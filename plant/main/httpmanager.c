#include "config.h"
#include "httpmanager.h"


#define MAX_HTTP_RECV_BUFFER 512
#define MAX_HTTP_OUTPUT_BUFFER 2048
static const char *TAG = "HTTP_CLIENT";

esp_err_t _http_event_handler(esp_http_client_event_t * evt){
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            const char* s = evt->data;
            int i1;
            if (1 == sscanf(s,"%*[^0123456789]%d", &i1)){
                if(i1 == 1){
                    printf("IT IS DAY\n");

                }else{
                    printf("IT IS NIGHT\n");

                }
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
            break;
    }
    return ESP_OK;
}

void http_call(char * url){
    esp_http_client_config_t config = {
        .url =url, 
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);

}

void http_POST_request(char * type, int timestamp, double value){
    char time[16];
    char value_s[50];
    snprintf(value_s, 50, "%f", value);
    
    char url[200] ="https://studev.groept.be/api/a21iot15/insert_measurement/";

    strcat(url,type);
    strcat(url,"/");
    strcat(url,itoa(timestamp,time,10));
    strcat(url,"/");
    strcat(url,value_s);
    printf("type %s timestamp %d value %f inserted in the database\n",type,timestamp,value);
    http_call(url);
}

void  http_GET_day_parameters(){
   char url[200] ="https://a21iot15.studev.groept.be/index.php/api/day";
   http_call(url);

}
