#ifndef RTI_H        /*prevent duplicated includes*/
#define RTI_H

/*Includes*/
#include "stdio.h"
#include "stdlib.h"
#include "projectglobals.h"
#include "pwm.h"
#include "seven_seg.h"
#include "led.h"
#include "lcd.h"
#include "control.h"
#include "queue_floor.h"

/*Macros*/
#define DEFAULT_TIME_OUT    0x17
#define ZERO_POINT_ONE_SEC  200     // 0.1초 = 100 ms
#define ZERO_POINT_FIVE_SEC 1000    // 0.5초 = 500 ms
#define ONE_SEC             2000    // 1초 = 1000 ms
#define TEN_MILLI_SEC       20      // 10 ms
#define FIVE_MILLI_SEC      10      // 5 ms
#define TWOFIVE_MILLI_SEC    5      // 2.5 ms
#define DIV                 12
#define LCD_OFFSET          0x44

// 시간 별 동작 정의
#define ACCELERATE_PERIOD       200     // 출발하고 2초동안 가속
#define DEACCELERATE_PERIOD1    500     // 도착하기 5초전부터 감속
#define DEACCELERATE_PERIOD2    300     // 도착하기 3초전까지 감속
#define DOOR_TIME               300     // 문 열고 닫기 3초
#define DOOR_OPEN               70      // 도착 후 0 ~ 0.5초 사이에 문이 열림
#define DOOR_CLOSE              70      // 도착 0.5초전 문이 닫힘

typedef unsigned char   u8;
typedef unsigned int    u32;

void rti_enable();
void rti_disable();
void init_rti();
void rti_service_ten_milli_sec();
void rti_handler(void);

#endif /*RTI_H*/
