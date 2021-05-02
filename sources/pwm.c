//#include "main.h"
#include "pwm.h"

/*
 * PWM0 -> A
 * PWM1 -> /A
 * PWM2 -> B
 * PWM3 -> /B
 *
 * PWM0, PWM1 ->  62.5kHz
 *
 * ���� Ŭ�� : 8MHz */


/**************************************************/
/*   PWM�� �ʱ�ȭ�Ѵ�.
/**************************************************/

void init_pwm(u8 clockwise) {
    if (clockwise) {
        Pwm.pwme.byte = PWME0 | PWME1 | PWME2 | PWME3;
        //Pwm.pwme.byte = ~(PWME0 | PWME1 | PWME2 | PWME3) ;  // PWM�� ��� ä��(0~3)�� ��Ȱ��ȭ �Ѵ�.

        Pwm.pwmpol.byte = PPOL0 | PPOL2;  // �� ä���� �ؼ��� �����Ѵ�. (A, B) -> /A/B -> A/B -> AB -> /AB

        Pwm.pwmclk.byte = 0x0;  // �� ä���� Ŭ��(A,B)�� �����Ѵ�.

        Pwm.pwmprclk.byte = PCKA | PCKB;  // �� ä���� Clock Prescale �� �����Ѵ�.

        Pwm.pwmcae.byte = CAE0 | CAE1;  // �߾� ����(Center Align)�� ä���� �����Ѵ�. (A, /A)

        // PWM control
        Pwm.pwmctl.byte = 0x00;

        // shutdown
        Pwm.pwmsdn.bit.pwm7en = 0;
    }
    else {
        Pwm.pwme.byte = PWME0 | PWME1 | PWME2 | PWME3;
        //Pwm.pwme.byte = ~(PWME0 | PWME1 | PWME2 | PWME3) ;  // PWM�� ��� ä��(0~3)�� ��Ȱ��ȭ �Ѵ�.

        Pwm.pwmpol.byte = PPOL0 | PPOL3;  // �� ä���� �ؼ��� �����Ѵ�. (A, /B) -> /AB -> AB -> A/B -> /A/B

        Pwm.pwmclk.byte = 0x0;  // �� ä���� Ŭ��(A,B)�� �����Ѵ�.

        Pwm.pwmprclk.byte = PCKA | PCKB;  // �� ä���� Clock Prescale �� �����Ѵ�.

        Pwm.pwmcae.byte = CAE0 | CAE1;  // �߾� ����(Center Align)�� ä���� �����Ѵ�. (A, /A)

        // PWM control
        Pwm.pwmctl.byte = 0x00;

        // shutdown
        Pwm.pwmsdn.bit.pwm7en = 0;
    }
}


/**************************************************/
/*   PWM�� �ֱ�� ��Ƽ�� �����Ѵ�.
/**************************************************/
// p: period, d: duty
void set_pwm(unsigned char p, unsigned char d) {
    // disable PWM channel
    //Pwm.pwme.byte = ~(PWME0 | PWME1 | PWME2 | PWME3) ;
    
    // �� ä���� �ֱ⸦ �����Ѵ�.
    Pwm.pwmper[0].byte = p >> 1;
    Pwm.pwmper[1].byte = p >> 1;

    Pwm.pwmper[2].byte = p;
    Pwm.pwmper[3].byte = p;

    // �� ä���� ��Ƽ�� �����Ѵ�.
    Pwm.pwmdty[0].byte = d >> 1;
    Pwm.pwmdty[1].byte = d >> 1;

    Pwm.pwmdty[2].byte = d;
    Pwm.pwmdty[3].byte = d;

    
    // PWM�� ��� ä��(0~3)�� Ȱ��ȭ �Ѵ�.
    //Pwm.pwme.byte = PWME0 | PWME1 | PWME2 | PWME3;
}
