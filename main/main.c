#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include <esp_timer.h>

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;

void blink_led()
{
    ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
    s_led_state = !s_led_state;
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);

}

void configure_led()
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void configure_timer()
{
     const esp_timer_create_args_t periodic_timer_args = {
            .callback = &blink_led,
            /* name is optional, but may help identify the timer when debugging */
            .name = "periodic"
     };

     esp_timer_handle_t periodic_timer;
     ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
     ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 2000000));

    

}

void app_main()
{

    /* Configure the peripheral according to the LED type */
    configure_led();
    configure_timer();

    while (1) {
    }
}