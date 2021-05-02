#ifndef RTI_H        /*prevent duplicated includes*/
#define RTI_H

/*Includes*/
#include "projectglobals.h"
#include "seven_seg.h"
#include "control.h"

/*Macros*/
#define DEFAULT_TIME_OUT    0x17
#define ZERO_POINT_ONE_SEC  200     // 0.1초
#define ZERO_POINT_FIVE_SEC 1000    // 0.5초
#define ONE_SEC             2000    // 1초

#define ONE_FLOOR_MOVING_TIME         50 // 5초
#define TWO_FLOOR_MOVING_TIME         100 // 10초

typedef unsigned char u8;
typedef unsigned int u32;

void init_rti(int s);
void rti_handler(void);
void rti_service_one_sec(void);
void rti_service_zero_point_one_sec(void);

#endif /*RTI_H*/
