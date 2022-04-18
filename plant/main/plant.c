#include "wifimanager.h"
#include "ADCmanager.h"
#include "httpmanager.h"
#include "config.h"
#include "mqttmanager.h"
#include "ledmanager.h"
extern esp_mqtt_client_handle_t client;
extern char wifi_connected;
extern char mqtt_config_finish;
extern float temp_array;
extern float volt_array;
float get_array_avg(float *);
void add_measurement(float *,float);
void task_temperature(void * param);
void task_moisture(void * param);
void task_light(void * param);
float binary_search_voltage(float);

static float light_array[RUN_AVG_LENGTH];
static float moisture_array[RUN_AVG_LENGTH];
static float temperature_array[RUN_AVG_LENGTH];

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

    // get user data from the database.

    //set GPIO direction
    // gpio_set_level to turn on and off
    ESP_ERROR_CHECK(gpio_reset_pin(GPIO_NUM_26)); // abort if not successful
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT)); // abort if not successful

	if(xTaskCreate(task_moisture,"moisture_sensor",2048,NULL,2,NULL)!=pdPASS) abort();
	if(xTaskCreate(task_temperature,"temperature_sensor",2048,NULL,2,NULL)!=pdPASS) abort();
	if(xTaskCreate(task_light,"light_sensor",2048,NULL,3,NULL)!=pdPASS) abort();
}

//when nothing is connected ADC reads 0.043030 V
void task_temperature(void * param){
    int index;
    int val;
    int avg;
    float voltage;
    float temperature;
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(60000);
    while(1){
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
        // get reading
        val = adc1_get_raw(ADC1_CHANNEL_6);
        voltage = adc_get_voltage(val);
        temperature = voltage/(3300);
        // check if it is reasonable
        if(temperature > 3.3 || temperature<0.05)continue;
        printf("temperature reading %f\n",temperature);

        // convert reading to temperature
        index = temperature*10-1;
        if(index > 33)index=33;
        if(index<0)index=0;
        temperature = temp_array[index];

        // add temperature to the array
        add_measurement(temperature_array,temperature); 
        // get the running avg
        avg = get_array_avg(temp_array); 
        //compare to the ideal value comparison in degrees
        // decide, valve open or not
        // HTTP request
    }
    vTaskDelete(NULL);
}
void task_moisture(void * param){
    int val;
    float voltage;
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(60000);
    while(1){
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
        // get reading
        val = adc1_get_raw(ADC1_CHANNEL_0);
        voltage = adc_get_voltage(val);
        // check if it is reasonable
        if(voltage > 3.3 || voltage<0.05)continue;
        printf("moisture reading %f\n",voltage/3300);

        //convert voltage to percentage
        float moisture = 100 - 100 * voltage/(3300);
        
        // add to the moisture array
        add_measurement(moisture_array,moisture); 

        // get the running avg
        avg = get_array_avg(moisture_array); 
        //compare to the ideal value comparison in percentage 
        // decide, valve open or not
        // HTTP request
    }
    vTaskDelete(NULL);
}
void task_light(void * param){
    int val;
    float voltage;
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(60000);
    while(1){
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
        // get reading
        val = adc1_get_raw(ADC1_CHANNEL_3);
        voltage = adc_get_voltage(val);
        // check if it is reasonable
        if(voltage > 3.3 || voltage<0.05)continue;
        printf("light reading %f\n",voltage/3300);

        // add to the array
        add_measurement(light_array,voltage/1000); 
        // get the running avg
        avg = get_array_avg(light_array); 
        // compare with the ideal value comparison in voltage 
        // decide, open lights or not 


        // HTTP request to write the data to the database

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
