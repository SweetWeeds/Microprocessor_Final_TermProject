#ifndef INTERRUPT_H        /*prevent duplicated includes*/
#define INTERRUPT_H

/*Includes*/
#include "projectglobals.h"
#include "atd.h"
#include "seven_seg.h"
#include "sci.h"
#include "dataframe.h"
#include "queue.h"
#include "stdio.h"

#define xint_enable()  {asm andcc   #0xBF;}
#define SW1_MASK_BIT 0x01
#define SW2_MASK_BIT 0x01
#define SW3_MASK_BIT 0x02

void ini_interrupt(void);
void interruptJ_function(void);
void interruptX_function(void);
  

#endif 
