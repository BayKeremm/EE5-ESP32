#include "wifimanager.h"
#include "ADCmanager.h"
#include "httpmanager.h"
#include "config.h"
#include "mqttmanager.h"
#include "ledmanager.h"

// globals
extern esp_mqtt_client_handle_t client;
extern char wifi_connected;
extern char mqtt_config_finish;
double idealParams[3];
double dayWait[2];
double ownershipId;

// statics
static float light_array[RUN_AVG_LENGTH];
static float moisture_array[RUN_AVG_LENGTH];
static float temperature_array[RUN_AVG_LENGTH];
static float volt_array[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3,
    1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4};
static float temp_array[] = {27.0, 26.6, 26.2, 25.8, 25.4, 25.0, 24.6, 24.2, 23.8, 23.4, 23.0, 
    22.6, 22.2, 21.8, 21.4, 21.0, 20.6, 20.2, 19.8, 19.4, 19.0, 18.6, 18.2, 17.8, 17.4, 16.9, 16.5, 16.1, 
    15.7, 15.3, 14.9, 14.4, 14.0};

// function prototypes
float get_array_avg(float *);
void add_measurement(float *,float);
void task_temperature(void * param);
void task_moisture(void * param);
void task_light(void * param);



void app_main(void)
{
    // init memory esp32
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
    // init ADC
    adc_init(); // ESP_ERROR_CHECK exits with abort() in case of error.

     //init led pwm
    led_pwm_init(); // ESP_ERROR_CHECK exits with abort() in case of error.

    // init wifi and connect 
    wifi_init_sta(); // ESP_ERROR_CHECK exits with abort() in case of error.


    // wait for wifi and mqtt

    while(wifi_connected == 0 || mqtt_config_finish == 0){
        if(wifi_connected == 1)
        MQTT_start(); // abort when not successfull
        vTaskDelay(3000 / portTICK_PERIOD_MS); 
        printf("waiting for wifi connection and mqtt config\n");
    }

    // get user data from the database and ideal parameters.
    http_GET_ideal_parameters();

    //set GPIO direction
    // gpio_set_level to turn on and off
    ESP_ERROR_CHECK(gpio_reset_pin(GPIO_NUM_25)); // abort if not successful
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT)); // abort if not successful
    gpio_set_level(GPIO_NUM_25,1);
    
    if(xTaskCreate(task_moisture,"moisture_sensor",2048,NULL,2,NULL)!=pdPASS) abort();
    if(xTaskCreate(task_temperature,"temperature_sensor",2048,NULL,2,NULL)!=pdPASS) abort();
    if(xTaskCreate(task_light,"light_sensor",2048,NULL,2,NULL)!=pdPASS) abort();
}

//when nothing is connected ADC reads 0.043030 V
void task_temperature(void * param){
    int index;
    int val;
    float run_avg;
    float temperature_voltage;
    float temperature;
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(60000);
    while(1){
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
        // get reading
        val = adc1_get_raw(ADC1_CHANNEL_6);
        temperature_voltage = adc_get_voltage(val);
        temperature_voltage = temperature_voltage/(3300);
        // check if it is reasonable
        if(temperature_voltage > 3300 || temperature_voltage < 50)continue;
        printf("voltage reading %f\n",temperature_voltage);

        // convert reading to temperature
        index = temperature_voltage*10-1;
        if(index > 33)index=33;
        if(index<0)index=0;
        temperature = temp_array[index];
        printf("temperature is %f\n",temperature);

        // add temperature to the array
        add_measurement(temperature_array,temperature_voltage); 
        // get the running avg
        run_avg = get_array_avg(temp_array); 
        //compare to the ideal value comparison in degrees
        if(run_avg > idealParams[0]){
            //TODO: room is too hot for the plant
        
        }

        // HTTP request
        http_POST_measurement_request("Temperature", run_avg);
    }
    vTaskDelete(NULL);
}
void task_moisture(void * param){
    int val;
    float run_avg;
    float moisture_voltage;
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(60000);
    while(1){
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
        // get reading
        val = adc1_get_raw(ADC1_CHANNEL_0);
        moisture_voltage = adc_get_voltage(val);
        // check if it is reasonable
        if(moisture_voltage > 3300 || moisture_voltage<50)continue;
        printf("moisture reading %f\n",moisture_voltage / 3300);
        moisture_voltage = moisture_voltage/3300;
        
        // add to the moisture array
        add_measurement(moisture_array,moisture_voltage); 

        // get the running avg
        run_avg = get_array_avg(moisture_array); 
        //compare to the ideal value 
        if(run_avg > idealParams[1]){
            //TODO:open valve
        
        }
        else{
            //TODO:close valve
        }
        // HTTP request
        http_POST_measurement_request("Moisture", run_avg);
    }
    vTaskDelete(NULL);
}
void task_light(void * param){
    char counter=0;
    int val;
    float run_avg;
    float light_voltage;
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount ();
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    
    const TickType_t xFrequency = pdMS_TO_TICKS(60000);// measurement frequency
    const TickType_t frequency_hour = pdMS_TO_TICKS(3600000);// measurement frequency

    // CUSTOM LOOP
    start:  
    http_GET_day_parameter();

    if(dayWait[0]==1){

        counter=0;
        gettimeofday(&current_time, NULL);
        time_t control_time = current_time.tv_sec / 3600 + dayWait[1];

        while(control_time - current_time.tv_sec/3600  > 0){
            gettimeofday(&current_time, NULL);
            xTaskDelayUntil( &xLastWakeTime, xFrequency );
           
            // get reading
            val = adc1_get_raw(ADC1_CHANNEL_3);
            light_voltage = adc_get_voltage(val);
            
            // check if it is reasonable
            if(light_voltage > 3300 || light_voltage < 50)continue;

            light_voltage = light_voltage/3300;

            // add to the array
            add_measurement(light_array,light_voltage); 
            
            // get the running avg
            run_avg = get_array_avg(light_array); 
            
            // compare with the ideal value comparison in voltage 
            if(run_avg > idealParams[2]){
                //TODO: open lights 
            
            }else{
                //TODO: close lights 
            }
            // HTTP request to write the data to the database
            http_POST_measurement_request("Light", run_avg);


        }
        goto start;
    
    }
    while(dayWait[0]==0){
        if(counter==dayWait[1]){
            goto start;
        }
        xTaskDelayUntil( &xLastWakeTime, frequency_hour );
        counter++;
    }

    vTaskDelete(NULL);
}


void add_measurement(float*array,float value){
   int i;
   for(i=RUN_AVG_LENGTH-1;i>0;i--){
        array[i] = array[i-1];
   }
   array[0] = value; 
    return;
}
float get_array_avg(float * array){
    float sum = 0;
    int i;
    for(i = 0;i<RUN_AVG_LENGTH;i++){
        sum+=array[i];
    }
    return sum / RUN_AVG_LENGTH;
}
