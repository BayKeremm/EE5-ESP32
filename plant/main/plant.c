
#include "wifimanager.h"
#include "ADCmanager.h"
#include "httpmanager.h"
#include "config.h"
#include "mqttmanager.h"
#include "ledmanager.h"
extern esp_mqtt_client_handle_t client;
extern char wifi_connected;
extern char mqtt_config_finish;
const float volt_array[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3,
    1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4};

const float temp_array[] = {27.0, 26.6, 26.2, 25.8, 25.4, 25.0, 24.6, 24.2, 23.8, 23.4, 23.0, 
    22.6, 22.2, 21.8, 21.4, 21.0, 20.6, 20.2, 19.8, 19.4, 19.0, 18.6, 18.2, 17.8, 17.4, 16.9, 16.5, 16.1, 
    15.7, 15.3, 14.9, 14.4, 14.0};

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
    gpio_reset_pin(GPIO_NUM_26);
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);
    
    // init ADC
    adc_init();

    // init led pwm
    led_pwm_init();

    // init wifi and connect 
    wifi_init_sta();

    // wait for wifi and mqtt
    while(wifi_connected == 0 || mqtt_config_finish == 0){
        if(wifi_connected == 1)
        MQTT_start(); // when wifi is connected init mqtt
        vTaskDelay(3000 / portTICK_PERIOD_MS); 
        printf("waiting for wifi connection and mqtt config\n");
    }

	xTaskCreate(task_moisture,"moisture_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_temperature,"temperature_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_light,"light_sensor",2048,NULL,2,NULL);
}

void task_temperature(void * param){

    int val;
    float voltage;
    float temperature;
    TickType_t xLastWakeTime;
    BaseType_t xWasDelayed;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    while(1){
        val = adc1_get_raw(ADC1_CHANNEL_6);
        voltage = adc_get_voltage(val);
        temperature = voltage/(3300);
        int index = reading*10-1;
        if(index > 33)index=33;
        if(index<0)index=0;
        temperature = temp_array[index];
        add_measurement(temperature_array,temperature); 
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
    vTaskDelete(NULL);
}
void task_moisture(void * param){
    int val;
    float voltage;
    TickType_t xLastWakeTime;
    BaseType_t xWasDelayed;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    while(1){
        val = adc1_get_raw(ADC1_CHANNEL_0);
        voltage = adc_get_voltage(val);
        float moisture = 100 - 100 * voltage/(3300);
        printf("(MOISTURE)The moisture percentage is %f\n",moisture); 
        add_measurement(moisture_array,moisture); 
        printf("(MOISTURE)The average is %f V\n", get_array_avg(moisture_array));
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
    vTaskDelete(NULL);
}
void task_light(void * param){
    int val;
    float voltage;
    TickType_t xLastWakeTime;
    BaseType_t xWasDelayed;
    xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xFrequency = pdMS_TO_TICKS(1000);
    while(1){
        val = adc1_get_raw(ADC1_CHANNEL_3);
        voltage = adc_get_voltage(val);
        printf("(LDR)The voltage value is %f V\n", voltage/1000);
        add_measurement(light_array,voltage/1000); 
        printf("(LDR)The average is %f V\n", get_array_avg(light_array));
        xTaskDelayUntil( &xLastWakeTime, xFrequency );
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
}
