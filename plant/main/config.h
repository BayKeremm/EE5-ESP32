#ifndef CONFIG_H_
#define CONFIG_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_tls.h"
#include "esp_http_client.h"

#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "esp_smartconfig.h"


#include "mqtt_client.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"

#include "driver/ledc.h"

#include "nvs.h"
#include <stdint.h>
#include <stdbool.h>


#define RUN_AVG_LENGTH 5

#include "lwip/err.h"
#include "lwip/sys.h"

#define DAY_URL "https://a21iot15.studev.groept.be/index.php/api/day"
#define INSERT_URL "https://a21iot15.studev.groept.be/index.php/api/put/" 
#define TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImRvbG1hIiwiZXhwIjoxNjUzMjk1NTA5fQ.31Jhv4f6xLBw7ct5qugHWudc11E_WZLlj-nTc0trr4g"
// Database paramters
#define ENUM_TEMPERATURE "Temperature"
#define ENUM_MOISTURE "Moisture"
#define ENUM_LIGHT "Light"

// wifi paramters
#define ESP_WIFI_SSID "keremap"
#define ESP_WIFI_PASS "vtbm5940"
#define ESP_MAX_RETRY 5

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define ESPTOUCH_DONE_BIT BIT2

#define BROKER_URI "mqtt://35.156.9.114:1883"
const float volt_array[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3,
    1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4};

const float temp_array[] = {27.0, 26.6, 26.2, 25.8, 25.4, 25.0, 24.6, 24.2, 23.8, 23.4, 23.0, 
    22.6, 22.2, 21.8, 21.4, 21.0, 20.6, 20.2, 19.8, 19.4, 19.0, 18.6, 18.2, 17.8, 17.4, 16.9, 16.5, 16.1, 
    15.7, 15.3, 14.9, 14.4, 14.0};

#endif  //CONFIG
