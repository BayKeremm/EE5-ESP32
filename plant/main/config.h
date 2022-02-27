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

#include "lwip/err.h"
#include "lwip/sys.h"

#define ENUM_TEMPERATURE "Temperature"
#define ENUM_MOISTURE "Moisture"
#define ENUM_LIGHT "Light"

#define ESP_WIFI_SSID "modem"
#define ESP_WIFI_PASS "853211kerem"
#define ESP_MAX_RETRY 5

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
/*typedef struct {
    double value;
    int time;
    char * type;
}datavalues_t;
*/
#endif  //CONFIG
