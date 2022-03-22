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

#include "esp_sntp.h"

#define RUN_AVG_LENGTH 5

#include "lwip/err.h"
#include "lwip/sys.h"

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
#define DAY_PARAMETERS_URI = "https://a21iot15.studev.groept.be/index.php/api/day"

// ADC paramters 


#endif  //CONFIG
