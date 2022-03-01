/*
    Questions:
        1. How the task priorities work, and how to give CPU time for lower priority tasks?
        2. How to use the QUEUE API for the shared data structure?
        3. Call http request after every measurement ?
*/

#include "wifimanager.h"
#include "ADCmanager.h"
#include "httpmanager.h"
#include "config.h"
void task_temperature(void * param);
void task_moisture(void * param);
void task_light(void * param);
void task_MQTT(void * param);



void app_main(void)
{
	// init memory
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
	// init WIFI
	//wifi_init_sta();
    // init ADC
    adc_init();
	// LDR 
	xTaskCreate(task_light,"light_sensor",2048,NULL,2,NULL);


    //http_POST_request(ENUM_MOISTURE,9876,14.04);
	//xTaskCreate(task_database,"database_data",2048,NULL,2,NULL);
	/*
	xTaskCreate(task_temperature,"temperature_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_moisture,"moisture_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_light,"light_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_MQTT,"app_communication",2048,NULL,2,NULL);
    */
}

void task_temperature(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
void task_moisture(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
void task_light(void * param){
    int val;
    while(1){
        val = adc1_get_raw(ADC1_CHANNEL_0);
        printf("The raw value is %d", val);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task_MQTT(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
