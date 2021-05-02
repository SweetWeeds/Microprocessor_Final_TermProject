#include "rti.h"

extern u8 CurrentMode;
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

void rti_service_one_sec(void) {

}

/**
 * 0.1초마다 호출
 */
void rti_service_zero_point_one_sec(void) {
    static u32 count = 0;
    // 이동중인 경우
    if (CurrentMode == ONE_TWO || CurrentMode == TWO_ONE || CurrentMode == ONE_TWO) {
        if (count >= ONE_FLOOR_MOVING_TIME) {
            count = 0;
        }
    }
}

/*************************************************/
/*  리얼타임 인터럽트가 발생할 때의 동작을 정의한다. */
/*************************************************/

/* 0.5초 마다 rti_handler 실행 */
void rti_handler(void)
{
	static u32 os_count = 0;
    static u32 zpos_count = 0;
	
	os_count++;
    zpos_count++;

	if (os_count >= ONE_SEC) {
        // 1초마다 실행
		rti_service_one_sec();
  		os_count = 0;
	}

    if (zpos_count >= ZERO_POINT_ONE_SEC) {
        // 0.1초마다 실행
        rti_service_zero_point_one_sec();
        zpos_count = 0;
    }

	// clear flag
    Crg.crgflg.bit.rtif = 1;    // 실시간 인터럽트 플래그 초기화
}
