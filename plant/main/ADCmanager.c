#include "config.h"
#include "ADCmanager.h"

static esp_adc_cal_characteristics_t adc1_chars;
void adc_init(void){
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_9));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_3,ADC_ATTEN_DB_11));
    
}
int adc_get_voltage(int reading){
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_9, 0, &adc1_chars);
    
    return esp_adc_cal_raw_to_voltage(reading, &adc1_chars);

}
