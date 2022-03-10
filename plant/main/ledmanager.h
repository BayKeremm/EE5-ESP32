#ifndef LED_H_
#define LED_H_
void led_pwm_duty_update(uint32_t duty);
void led_pwm_init(void);
void led_on(void);
void led_off(void);

#endif

