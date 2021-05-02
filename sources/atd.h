#ifndef ATD_H        /*prevent duplicated includes*/
#define ATD_H

/*Includes*/
#include "projectglobals.h"

#define ANALOG_INPUT_CHANNEL 0
#define ATDCTL2_INIT 0x80
#define ATDCTL3_INIT 0x20
#define ATDCTL4_INIT 0x6d
#define ATDCTL5_INIT 0xa0
#define SCF_SET      0x80

#define VR_ZERO     439
#define VR_ONE      467
#define VR_TWO      495
#define VR_THREE    523
#define VR_FOUR     551
#define VR_FIVE     579
#define VR_SIX      607
#define VR_SEVEN    635
#define VR_EIGHT    663
#define VR_NINE     696

void init_atd0(void);
int get_atd0(int channel);
unsigned char convert_value(unsigned int cnt);

#endif /*SCI_H*/
