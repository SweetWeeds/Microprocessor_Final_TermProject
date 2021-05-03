#include "rti.h"

extern u32 TargetFloor;	// 가고자 하는 층
extern u32 CurrentFloor;	// 현재 층 (1층: 1000, 1~2층 사이: 1001~1999 ...)
extern u8 isMoving;
u32 doorStatus = 0;
//unsigned char period = LOW_SPEED;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

/*************************************************/
/*  리얼타임 인터럽트를 초기화 한다.*/
/*************************************************/
void init_rti() {
	//scaler = s;
	Crg.rtictl.byte = DEFAULT_TIME_OUT;     //리얼타임 인터럽트의 속도 결정(0.5ms 로 하시오)
	Crg.crgint.byte |= 0b10000000;		//리얼타임 인터럽트 enable
}

/**
 * 10ms마다 호출: 엘리베이터의 층이 1/1000만큼 이동 (1층 이동에 10초 소요)
 */
void rti_service_ten_milli_sec() {
    static u32 count = 0;
    static u32 pwm_period = LOW_SPEED;	// 모터 주기
    u32 delta = (TargetFloor == CurrentFloor ? 0 : (TargetFloor > CurrentFloor ? +1 : -1));
    
    if (delta == 0) {
        count = 0;
        // 모터 정지
        disable_pwm();
        // 정지 플래그
        isMoving = FALSE;
        // period 초기화
        period = LOW_SPEED;
    }
    else {
        // 초기화
        if (count == 0) {
            // 모터 방향 결정 & 초기화
            init_pwm(TargetFloor > CurrentFloor);
            pwm_period = LOW_SPEED;
        }
        CurrentFloor += delta;
        count++;
		// 세븐 세그먼트 회전 (0.1s마다)
		if (count % 1000 == 0) rotate_7seg(TargetFloor > CurrentFloor);
        // 1. 모터 가속 (count가 홀수일때 호출)
        if (count <= ACCELERATE_PERIOD && count & 1) {
            pwm_period++;
            set_pwm(period, period / 2);
        }
        // 2. 모터 감속 (count가 홀수일때 호출)
        if (TargetFloor - DEACCELERATE_PERIOD1 <= CurrentFloor && CurrentFloor < TargetFloor - DEACCELERATE_PERIOD2 && count & 1) {
            pwm_period--;
            set_pwm(period, period / 2);
        }
        // 3. 모터 정지
        if (TargetFloor - DEACCELERATE_PERIOD2 <= CurrentFloor) {
			set_7segment(CurrentFloor / 1000);
            disable_pwm();
        }
        // 4. 문 열기
        if (TargetFloor - DOOR_OPEN <= CurrentFloor && CurrentFloor < TargetFloor - DOOR_CLOSE && (count % 100 == 0)) {
            doorStatus++;
            set_door(doorStatus);
        }
        // 5. 문 닫기
        if (TargetFloor - DOOR_CLOSE <= CurrentFloor && (count % 100 == 0)) {
            doorStatus--;
	    	set_door(doorStatus);
		}
		if (TargetFloor <= CurrentFloor) {
			count = 0;
			isMoving = FALSE;
		}
	}
}

/*************************************************/
/*  리얼타임 인터럽트가 발생할 때의 동작을 정의한다. */
/*************************************************/

/* 0.5초 마다 rti_handler 실행 */
void rti_handler(void)
{
    static u32 tms_count = 0;
    tms_count++;

    if (tms_count >= TEN_MILLI_SEC) {
	if (isMoving) rti_service_zero_point_one_sec();
	tms_count = 0;
    }

    // clear flag
    Crg.crgflg.bit.rtif = 1;    // 실시간 인터럽트 플래그 초기화
}
