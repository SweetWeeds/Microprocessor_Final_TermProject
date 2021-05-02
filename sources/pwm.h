#ifndef PWM_H        /*prevent duplicated includes*/
#define PWM_H

/*Includes*/
#include "projectglobals.h"

#define PWMCAE_LEFT_ALIGN   0x00
#define PWMCAE_CENTER_ALIGN 0x01

typedef unsigned char u8;

void init_pwm(void);
void set_pwm(unsigned char p, unsigned char d);

#endif