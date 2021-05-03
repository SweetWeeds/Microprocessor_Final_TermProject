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
 * 버스 클럭 : 8MHz */

// PWM 비활성화
void disable_pwm() {
    Pwm.pwme.byte = ~(PWME0 | PWME1 | PWME2 | PWME3);
}

// PWM 활성화
void enable_pwm() {
    Pwm.pwme.byte = PWME0 | PWME1 | PWME2 | PWME3;
}

/**************************************************/
/*   PWM을 초기화한다.
/**************************************************/

void init_pwm(u8 clockwise) {
    if (clockwise) {
        Pwm.pwme.byte = PWME0 | PWME1 | PWME2 | PWME3;
        //Pwm.pwme.byte = ~(PWME0 | PWME1 | PWME2 | PWME3) ;  // PWM의 모든 채널(0~3)을 비활성화 한다.

        Pwm.pwmpol.byte = PPOL0 | PPOL2;  // 각 채널의 극성을 설정한다. (A, B) -> /A/B -> A/B -> AB -> /AB

        Pwm.pwmclk.byte = 0x0;  // 각 채널의 클럭(A,B)을 선택한다.

        Pwm.pwmprclk.byte = PCKA | PCKB;  // 각 채널의 Clock Prescale 을 설정한다.

        Pwm.pwmcae.byte = CAE0 | CAE1;  // 중앙 정렬(Center Align)할 채널을 설정한다. (A, /A)

        // PWM control
        Pwm.pwmctl.byte = 0x00;

        // shutdown
        Pwm.pwmsdn.bit.pwm7en = 0;
    }
    else {
        Pwm.pwme.byte = PWME0 | PWME1 | PWME2 | PWME3;
        //Pwm.pwme.byte = ~(PWME0 | PWME1 | PWME2 | PWME3) ;  // PWM의 모든 채널(0~3)을 비활성화 한다.

        Pwm.pwmpol.byte = PPOL0 | PPOL3;  // 각 채널의 극성을 설정한다. (A, /B) -> /AB -> AB -> A/B -> /A/B

        Pwm.pwmclk.byte = 0x0;  // 각 채널의 클럭(A,B)을 선택한다.

        Pwm.pwmprclk.byte = PCKA | PCKB;  // 각 채널의 Clock Prescale 을 설정한다.

        Pwm.pwmcae.byte = CAE0 | CAE1;  // 중앙 정렬(Center Align)할 채널을 설정한다. (A, /A)

        // PWM control
        Pwm.pwmctl.byte = 0x00;

        // shutdown
        Pwm.pwmsdn.bit.pwm7en = 0;
    }
}


/**************************************************/
/*   PWM의 주기와 두티를 설정한다.
/**************************************************/
// p: period, d: duty
void set_pwm(unsigned char p, unsigned char d) {
    // disable PWM channel
    //Pwm.pwme.byte = ~(PWME0 | PWME1 | PWME2 | PWME3) ;
    
    // 각 채널의 주기를 설정한다.
    Pwm.pwmper[0].byte = p >> 1;
    Pwm.pwmper[1].byte = p >> 1;

    Pwm.pwmper[2].byte = p;
    Pwm.pwmper[3].byte = p;

    // 각 채널의 듀티를 설정한다.
    Pwm.pwmdty[0].byte = d >> 1;
    Pwm.pwmdty[1].byte = d >> 1;

    Pwm.pwmdty[2].byte = d;
    Pwm.pwmdty[3].byte = d;

    
    // PWM의 모든 채널(0~3)을 활성화 한다.
    //Pwm.pwme.byte = PWME0 | PWME1 | PWME2 | PWME3;
}
