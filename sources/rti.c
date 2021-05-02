#include "rti.h"

extern u8 CurrentMode;
int scaler;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

/*************************************************/
/*  ����Ÿ�� ���ͷ�Ʈ�� �ʱ�ȭ �Ѵ�.*/
/*************************************************/
void init_rti(int s)
{
	scaler = s;
	Crg.rtictl.byte = DEFAULT_TIME_OUT;     //����Ÿ�� ���ͷ�Ʈ�� �ӵ� ����(0.5ms �� �Ͻÿ�)
	Crg.crgint.byte |= 0b10000000;		//����Ÿ�� ���ͷ�Ʈ enable
}

void rti_service_one_sec(void) {

}

/**
 * 0.1�ʸ��� ȣ��
 */
void rti_service_zero_point_one_sec(void) {
    static u32 count = 0;
    // �̵����� ���
    if (CurrentMode == ONE_TWO || CurrentMode == TWO_ONE || CurrentMode == ONE_TWO) {
        if (count >= ONE_FLOOR_MOVING_TIME) {
            count = 0;
        }
    }
}

/*************************************************/
/*  ����Ÿ�� ���ͷ�Ʈ�� �߻��� ���� ������ �����Ѵ�. */
/*************************************************/

/* 0.5�� ���� rti_handler ���� */
void rti_handler(void)
{
	static u32 os_count = 0;
    static u32 zpos_count = 0;
	
	os_count++;
    zpos_count++;

	if (os_count >= ONE_SEC) {
        // 1�ʸ��� ����
		rti_service_one_sec();
  		os_count = 0;
	}

    if (zpos_count >= ZERO_POINT_ONE_SEC) {
        // 0.1�ʸ��� ����
        rti_service_zero_point_one_sec();
        zpos_count = 0;
    }

	// clear flag
    Crg.crgflg.bit.rtif = 1;    // �ǽð� ���ͷ�Ʈ �÷��� �ʱ�ȭ
}
