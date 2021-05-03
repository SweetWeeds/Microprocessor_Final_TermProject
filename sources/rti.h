#ifndef RTI_H        /*prevent duplicated includes*/
#define RTI_H

/*Includes*/
#include "projectglobals.h"
#include "pwm.h"
#include "seven_seg.h"
#include "led.h"
#include "control.h"

/*Macros*/
#define DEFAULT_TIME_OUT    0x17
#define ZERO_POINT_ONE_SEC  200     // 0.1초 = 100 ms
#define ZERO_POINT_FIVE_SEC 1000    // 0.5초 = 500 ms
#define ONE_SEC             2000    // 1초 = 1000 ms
#define TEN_MILLI_SEC       20      // 10 ms

// 시간 별 동작 정의
#define ACCELERATE_PERIOD       100     // 출발하고 1초동안 가속
#define DEACCELERATE_PERIOD1    500     // 도착하기 5초 ~ 4초전까지 감속
#define DEACCELERATE_PERIOD2    400
#define DOOR_OPEN               400     // 4초~3초까지 문이 열림
#define DOOR_CLOSE              200     // 1초~0초까지 문이 닫힘

typedef unsigned char   u8;
typedef unsigned int    u32;

void init_rti();
void rti_service_ten_milli_sec();
void rti_handler(void);

#endif /*RTI_H*/
