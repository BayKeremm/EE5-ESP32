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

#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"
#include "time.h"
#include "sys/time.h"
#include "nvs.h"
#include <stdint.h>
#include <stdbool.h>

#define RUN_AVG_LENGTH 5

#include "lwip/err.h"
#include "lwip/sys.h"

// Database paramters
#define ENUM_TEMPERATURE "Temperature"
#define ENUM_MOISTURE "Moisture"
#define ENUM_LIGHT "Light"

// wifi paramters
//#define ESP_WIFI_SSID "modem"
//#define ESP_WIFI_PASS "password" no need with smart config.
#define ESP_MAX_RETRY 5

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define ESPTOUCH_DONE_BIT BIT2

// ADC paramters 


#endif  //CONFIG
