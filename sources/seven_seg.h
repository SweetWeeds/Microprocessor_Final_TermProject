#ifndef SEVEN_SEG_H        /*prevent duplicated includes*/
#define SEVEN_SEG_H

/* Includes */
#include "projectglobals.h"

/* Macros */
#define SEVEN_SEGMENT_A   0x01
#define SEVEN_SEGMENT_B   0x02
#define SEVEN_SEGMENT_C   0x04
#define SEVEN_SEGMENT_D   0x08
#define SEVEN_SEGMENT_E   0x10
#define SEVEN_SEGMENT_F   0x20
#define SEVEN_SEGMENT_G   0x40
#define SEVEN_SEGMENT_DP  0x80

typedef enum {
    CLOCK_WISE = 0,
    COUNTER_CLOCK_WISE = 1
} DIRECTION;

void init_seven_seg(void);
void rotate_7seg(void);
void set_7segment(unsigned int number);

#endif /* SEVEN_SEG */
