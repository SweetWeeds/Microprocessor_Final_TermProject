#ifndef LED_H        /*prevent duplicated includes*/
#define LED_H

/*Includes*/
#include "projectglobals.h"

#define DDRB_LED_MASK_BIT 0xff
#define DDRM_LED_MASK_BIT 0xc0
#define UPPER_TWO_BIT     0x300
#define LOWER_EIGHT_BIT   0x0ff

void init_led(void);
void set_led(unsigned int digit);
void set_door(unsigned int open);
void set_led_counter(unsigned int cnt);

#endif /* LED_H */