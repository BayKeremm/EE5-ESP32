#include "config.h"


#define SPP_TAG "SPP_WIFI_CONFIG"
#define SPP_SERVER_NAME "SPP_SERVER"
#define DEVICE_NAME "SPP_SERVER_PLANT"

static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_NONE;
static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;
static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;



static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t * param){
        
    char buf[1024];
    char spp_data[256];

    switch (event){
        
        case ESP_SPP_INIT_EVT:
            ESP_LOGI(SPP_TAG, "ESP_SPP_INIT_EVT");
            esp_bt_dev_set_device_name(DEVICE_NAME);
            esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
            esp_spp_start_srv(sec_mask,role_slave,0,SPP_SERVER_NAME);
            break;
        case ESP_SPP_DISCOVERY_COMP_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_DISVOCERY_COMP_EVT");
            break;

        case ESP_SPP_OPEN_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_OPEN_EVT");
            break;
        case ESP_SPP_CLOSE_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_CLOSE_EVT");
            break;
        case ESP_SPP_START_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_START_EVT");
            break;
        case ESP_SPP_CL_INIT_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_CL_INIT_EVT");
            break;
        
        case ESP_SPP_DATA_IND_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_DATA_IND_EVT len=%d handle=%d",param->data_ind.len, param->data_ind.handle);
                
            if(param->data_ind.len < 1023){
                snprintf(buf,(size_t)param->data_ind.len,(char*)param->data_ind.data);
                printf("%s\n",buf);
                sprintf(spp_data, "KEREM OKYAY %d\n",param->data_ind.len);
                esp_spp_write(param->write.handle,strlen(spp_data),(uint8_t *)spp_data);
            }else{
                esp_log_buffer_hex("",param->data_ind.data,param->data_ind.len);
            }
            break;
        case ESP_SPP_CONG_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_CONG_EVT");
            break;
        case ESP_SPP_WRITE_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_WRITE_EVT");
            printf("kerem okyay");
            break;
        case ESP_SPP_SRV_OPEN_EVT:
            ESP_LOGI(SPP_TAG,"ESP_SPP_SRV_OPEN_EVT");
            break;
        default:
        break;

    }
        
}


void bluetooth_init(void){
    
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if (esp_bt_controller_init(&bt_cfg) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize controller failed: \n", __func__); 
        return;
    }

    if (esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable controller failed: \n", __func__);
        return;
    }

    if (esp_bluedroid_init() != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize bluedroid failed: \n", __func__);
        return;
    }

    if (esp_bluedroid_enable() != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable bluedroid failed: \n", __func__);
        return;
    }

    if (esp_spp_register_callback(esp_spp_cb) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp register failed: \n", __func__);
        return;
    }

    if (esp_spp_init(esp_spp_mode) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp init failed: \n", __func__);
        return;
    }

}
