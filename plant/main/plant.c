/*
    Questions:
        1. How the task priorities work, and how to give CPU time for lower priority tasks?
        2. How to use the QUEUE API for the shared data structure?
        3. Call http request after every measurement ?
*/

#include "wifimanager.h"
#include "httpmanager.h"
#include "config.h"
void task_temperature(void * param);
void task_moisture(void * param);
void task_light(void * param);
void task_MQTT(void * param);



void app_main(void)
{
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
	wifi_init_sta();
    http_POST_request(ENUM_MOISTURE,9876,14.04);
	//xTaskCreate(task_database,"database_data",2048,NULL,2,NULL);
	/*
	xTaskCreate(task_temperature,"temperature_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_moisture,"moisture_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_light,"light_sensor",2048,NULL,2,NULL);
	xTaskCreate(task_MQTT,"app_communication",2048,NULL,2,NULL);
    */
}

/*
    task for the temperature sensor
    read the pin with ADC
    put it into the shared data structure
    go to sleep
*/
void task_temperature(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
/*
    task for the soil moisture sensor
    read the pin with ADC
    put it into the shared data structure
    go to sleep
*/
void task_moisture(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
/*
    task for the LDR 
    read the pin with ADC
    put it into the shared data structure
    go to sleep
*/
void task_light(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
/* 
    task to communicate with the android app 
    MQTT subscribe and publish
*/
void task_MQTT(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
