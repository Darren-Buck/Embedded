#ifndef BLINK_H
#define BLINK_H

#include <unistd.h>

#if !defined(RELEASE) && !defined(DEBUG)

void mock_initialize_led();
void mock_led_high();
void mock_led_low();

#define INIT_LED() mock_initialize_led()
#define LED_HIGH() mock_led_high()
#define LED_LOW() mock_led_low()

#else
void initialize_led();
void turn_on_led();
void turn_off_led();

// If we define RELEASE or DEBUG our delay is sleep
#define DELAY(duration) sleep(duration)
#define INIT_LED() initialize_led()
#define LED_HIGH() turn_on_led()
#define LED_LOW() turn_off_led()

#endif

#endif // BLINK_H