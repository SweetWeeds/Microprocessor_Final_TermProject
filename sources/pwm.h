#ifndef PWM_H        /*prevent duplicated includes*/
#define PWM_H

/*Includes*/
#include "projectglobals.h"

#define PWMCAE_LEFT_ALIGN   0x00
#define PWMCAE_CENTER_ALIGN 0x01

#define LOW_SPEED  254
#define HIGH_SPEED 190

typedef unsigned char u8;

void pwm_disable(void);
void pwm_enable(void);
void init_pwm(u8 clockwise);
void set_pwm(unsigned char p, unsigned char d);

#endif