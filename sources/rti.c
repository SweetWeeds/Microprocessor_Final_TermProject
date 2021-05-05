#include "rti.h"

extern u8 TX[];
extern u32 TargetFloor;	    // 가고자 하는 층
extern u32 CurrentFloor;	// 현재 층 (1층: 1000, 1~2층 사이: 1001~1999 ...)
extern u32 pwm_period_scaler;
extern u8  isMoving;

//unsigned char period = LOW_SPEED;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

void rti_enable() {
	Crg.crgint.byte |= 0b10000000;		//리얼타임 인터럽트 enable
}

void rti_disable() {
	Crg.crgint.byte &= 0b01111111;		//리얼타임 인터럽트 enable
}

/*************************************************/
/*  리얼타임 인터럽트를 초기화 한다.*/
/*************************************************/
void init_rti() {
	Crg.rtictl.byte = DEFAULT_TIME_OUT;     //리얼타임 인터럽트의 속도 결정(0.5ms 로 하시오)
    Crg.crgint.byte |= 0b10000000;		//리얼타임 인터럽트 enable
}

/**
 * 10ms마다 호출: 엘리베이터의 층이 1/1000만큼 이동 (1층 이동에 10초 소요)
 */
void rti_service_ten_milli_sec() {
    static u8 flag = FALSE;             // 함수 호출 플래그 (초기화 목적)
    static int isHigher = 0;            // 목적 층 > 현재 층: +, 목적 층 < 현재 층: -, 목적 층 == 현재 층: 0
    static u32 doorStatus = 0;          // 엘리베이터 문 열고 닫기 상태
    static int tcount = 0;              // 함수 호출 횟수
    static u32 pwm_period = LOW_SPEED;	// 모터 주기
    static int moving_time = 0;  // 이동시간 (10ms * moving_time)
    static int delta = 0;
    int left_time;
    
    if (!flag) {
        // 초기화
        flag = TRUE;
        isHigher = TargetFloor - CurrentFloor;
        doorStatus = 0;
        set_door(doorStatus);
        tcount = 0;
        pwm_period = LOW_SPEED;     // 최저 속도로 초기화 (LOW_SPEED = 254)
        moving_time = ((isHigher > 0) ? (TargetFloor - CurrentFloor) : (CurrentFloor - TargetFloor)) + DOOR_TIME;
        delta = (isHigher ? (isHigher ? +1 : -1) : 0);
        init_pwm(isHigher > 0);    // 모터 방향 결정
    }
    else if (tcount < moving_time) {
        tcount++;
        left_time = moving_time - tcount;
        // 세그먼트 회전
        if (tcount % 10 == 0 && DEACCELERATE_PERIOD2 <= left_time) {
            rotate_seg(isHigher > 0);
        }
        // 1. 모터 초기 가속
        if (tcount <= ACCELERATE_PERIOD && tcount % 10 == 0 && pwm_period > HIGH_SPEED) {
            pwm_period--;
            if (!(pwm_period & 1)) set_pwm(pwm_period, pwm_period >> 1);
        }
        // 2. 모터 감속 & 모터 정지
        else if (DEACCELERATE_PERIOD2 <= left_time && left_time <= DEACCELERATE_PERIOD1 && tcount % 10 == 0 && pwm_period < LOW_SPEED) {
            pwm_period++;
            if (!(pwm_period & 1)) set_pwm(pwm_period, pwm_period >> 1);
        }
        // 3. 문 열기 (3초 ~ 2.5초)
        else if ((DOOR_TIME - DOOR_OPEN) <= left_time && left_time < DOOR_TIME) {
            set_7segment(TargetFloor / 1000);
            pwm_disable();
            if (tcount % 9 == 0 && doorStatus < 5) {
                set_door(doorStatus++);
            }
        }
        // 4. 문 닫기 (2초 ~ 1.5초)
        else if (left_time < DOOR_CLOSE) {
            if (tcount % 9 == 0 && doorStatus > 0) {
                set_door(--doorStatus);
            }
        }
    }
    else {
        pwm_disable();
        isMoving = FALSE;
        CurrentFloor = TargetFloor;

        flag = FALSE;
    }
}

/*************************************************/
/*  리얼타임 인터럽트가 발생할 때의 동작을 정의한다. */
/*************************************************/

/* 0.5ms초 마다 rti_handler 실행 */
void rti_handler(void)
{
    static int count = 0;
    count++;

    if (count >= FIVE_MILLI_SEC) {
        if (isMoving) rti_service_ten_milli_sec();
        count = 0;
    }

    // clear flag
    Crg.crgflg.bit.rtif = 1;    // 실시간 인터럽트 플래그 초기화
}
