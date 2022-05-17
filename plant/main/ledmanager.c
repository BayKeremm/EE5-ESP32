#include "config.h"
#include "ledmanager.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (25) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (200) // Frequency in Hertz. Set frequency at 5 kHz)))))

void led_off(void){
    ledc_stop(LEDC_MODE, LEDC_CHANNEL, 0);

}
void led_pwm_init(void){
    ledc_timer_config_t ledc_timer = {
            .speed_mode       = LEDC_MODE,
            .timer_num        = LEDC_TIMER,
            .duty_resolution  = LEDC_DUTY_RES,
            .freq_hz          = LEDC_FREQUENCY,  
            .clk_cfg          = LEDC_AUTO_CLK
        };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
            .speed_mode     = LEDC_MODE,
            .channel        = LEDC_CHANNEL,
            .timer_sel      = LEDC_TIMER,
            .intr_type      = LEDC_INTR_DISABLE,
            .gpio_num       = LEDC_OUTPUT_IO,
            .duty           = 0, 
            .hpoint         = 0
        };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    
                            
}

void led_pwm_duty_update(uint32_t duty){
    led_pwm_init();
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE,LEDC_CHANNEL, duty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

}
