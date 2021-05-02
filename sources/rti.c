#include "rti.h"

extern u32 TargetFloor;	// 가고자 하는 층
extern u32 CurrentFloor;	// 현재 층 (1층: 1000, 1~2층 사이: 1001~1999 ...)
int scaler;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

/*************************************************/
/*  리얼타임 인터럽트를 초기화 한다.*/
/*************************************************/
void init_rti(int s)
{
	scaler = s;
	Crg.rtictl.byte = DEFAULT_TIME_OUT;     //리얼타임 인터럽트의 속도 결정(0.5ms 로 하시오)
	Crg.crgint.byte |= 0b10000000;		//리얼타임 인터럽트 enable
}

/**
 * 10ms마다 호출: 엘리베이터의 층이 1/1000만큼 이동 (1층 이동에 10초 소요)
 */
void rti_service_ten_milli_sec() {
    u32 delta = (TargetFloor == CurrentFloor ? 0 : (TargetFloor > CurrentFloor ? +1 : -1));
    if (delta) {
	CurrentFloor += delta;
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
	rti_service_zero_point_one_sec();
	tms_count = 0;
    }

    // clear flag
    Crg.crgflg.bit.rtif = 1;    // 실시간 인터럽트 플래그 초기화
}
