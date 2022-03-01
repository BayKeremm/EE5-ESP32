#include "config.h"
#include "ADCmanager.h"

void adc_init(void){
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);
    
}
