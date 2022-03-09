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
#include "mqttmanager.h"
extern esp_mqtt_client_handle_t client;
extern char wifi_connected;
extern char mqtt_config_finish;

float get_array_avg(float *);
void add_measurement(float *,float);
void task_temperature(void * param);
void task_moisture(void * param);
void task_light(void * param);
void task_MQTT(void * param);
void task_wifi(void * param);

static float light_array[RUN_AVG_LENGTH];
static float moisture_array[RUN_AVG_LENGTH];
//static float temperature_array[RUN_AVG_LENGTH];



void app_main(void)
{
	// init memory
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
	
    wifi_init_sta();
    
    
    while(wifi_connected == 0 || mqtt_config_finish == 0){
        if(wifi_connected == 1)
        MQTT_start();
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        printf("waiting for wifi connection and mqtt config\n");
    }
    int msg_id = esp_mqtt_client_publish(client, "/EE5iot15/warnings", "This is a message from the app_main task", 0, 1, 1);
    
         
    
    //adc_init();
	// LDR 
	//xTaskCreate(task_moisture,"moisture_sensor",2048,NULL,2,NULL);
	//xTaskCreate(task_light,"light_sensor",2048,NULL,2,NULL);

	// init WIFI
	//xTaskCreate(task_wifi,"wifi",2048,NULL,2,NULL);
    // init ADC
    //adc_init();
	// LDR 
	//xTaskCreate(task_moisture,"moisture_sensor",2048,NULL,2,NULL);
	//xTaskCreate(task_light,"light_sensor",2048,NULL,2,NULL);


    //http_POST_request(ENUM_MOISTURE,9876,14.04);
}
void task_wifi(void*param){
    while(1){
	    wifi_init_sta();
    
    }
    vTaskDelete(NULL);
}

void task_temperature(void * param){
    while(1){
    
    }
    vTaskDelete(NULL);
}
void task_moisture(void * param){
    int val;
    float voltage;
    while(1){
        val = adc1_get_raw(ADC1_CHANNEL_0);
        voltage = adc_get_voltage(val);
        float moisture = 100 - 100 * voltage/(3300);
        printf("(MOISTURE)The moisture percentage is %f\n",moisture); 
        add_measurement(moisture_array,moisture); 
        printf("(MOISTURE)The average is %f V\n", get_array_avg(moisture_array));
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task_light(void * param){
    int val;
    float voltage;
    while(1){
        val = adc1_get_raw(ADC1_CHANNEL_3);
        voltage = adc_get_voltage(val);
        printf("(LDR)The voltage value is %f V\n", voltage/1000);
        add_measurement(light_array,voltage/1000); 
        printf("(LDR)The average is %f V\n", get_array_avg(light_array));
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task_MQTT(void * param){
    while(1){
         
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
