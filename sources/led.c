#include "led.h"

/*******************************************************
 *  BAR-LED에 사용되는 포트를 초기화 한다.               *
 *******************************************************/

void init_led(void) {
    // 포트 B와 포트 M 을 출력으로 설정
    Regs.ddrb.byte = DDRB_LED_MASK_BIT;
    Pim.ddrm.byte = DDRM_LED_MASK_BIT;
  
    // 포트 B와 포트 M 에 연결된 모든 LED를 끔
    Regs.portb.byte = DDRB_LED_MASK_BIT;
    Pim.ptm.byte = DDRM_LED_MASK_BIT;
}

/*******************************************************
 *  10비트의 숫자를 입력하면 그 값을 BAR-LED에 출력한다.  *
 *  0b11110000 = OFF OFF OFF OFF ON ON ON ON           *
 *******************************************************/
void set_led(unsigned int digit) {
    unsigned char upper_digit, lower_digit;
    digit = ~digit;
    
    upper_digit = (digit & UPPER_TWO_BIT) >> 2; // 10 비트 중에서 상위 2 비트의 값을 추출, 6,7비트 위치로 이동

    lower_digit = digit & LOWER_EIGHT_BIT;      // 10 비트 중에서 하위 8 비트의 값만 추출

    Pim.ptm.byte = upper_digit;     // 상위 2비트의 값을 포트 M에 출력
    Regs.portb.byte = lower_digit;  // 하위 8비트의 값을 포트 B에 출력
}

void door(unsigned int open) {
    if (open == 0) set_led(0b11111111);
    else if (open == 1) set_led(0b11100111);
    else if (open == 2) set_led(0b11000011);
    else if (open == 3) set_led(0b10000001);
    else if (open == 4) set_led(0b00000000);
}

void set_led_counter(unsigned int cnt) {
    unsigned int digit = 0;
    unsigned int i = 0;

    for (i = 0; i < cnt; i++) {
        digit = digit | (0x01 << i);
    }

    set_led(digit);
}
