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
 *  ex) 0b0000000000 = 0x000: 모든 LED를 OFF           *
 *      0b1111111111 = 0x3ff: 모든 LED를 ON            *
 *      0b1000000000 = 0x200: 가장 오른쪽의 LED를 ON    *
 *      0b0000000001 = 0x001: 가장 왼쪽의 LED를 ON      *
 *******************************************************/
void set_led(unsigned int digit) {
    unsigned char upper_digit, lower_digit;
    
    digit = ~digit;   // 입력 값 반전. LED의 ON/OFF를 직관적으로 하기 위함.

    upper_digit = (digit & UPPER_TWO_BIT) >> 2; // 10 비트 중에서 상위 2 비트의 값을 추출, 6,7비트 위치로 이동
    
    lower_digit = digit & LOWER_EIGHT_BIT;    // 10 비트 중에서 하위 8 비트의 값만 추출

    Pim.ptm.byte = upper_digit;  // 상위 2비트의 값을 포트 M에 출력
    Regs.portb.byte = lower_digit; // 하위 8비트의 값을 포트 B에 출력
}

void set_door(unsigned int open) {
    if (open == 0) set_led(0b1111111111);
    else if (open == 1) set_led(0b1111001111);
    else if (open == 2) set_led(0b1110000111);
    else if (open == 3) set_led(0b1100000011);
    else if (open == 4) set_led(0b0000000000);
    else set_led(0b1111111111);
}

void set_led_counter(unsigned int cnt) {
    unsigned int digit = 0;
    unsigned int i = 0;

    for (i = 0; i < cnt; i++) {
        digit = digit | (0x01 << i);
    }

    set_led(digit);
}
