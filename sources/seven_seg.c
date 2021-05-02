#include "seven_seg.h"

/*******************************************************
 *  7-Segment에 사용되는 포트를 초기화 한다.             *
 *******************************************************/
void init_seven_seg(void)
{
  // 포트 H를 출력 설정
  Pim.ddrh.byte = 0xff;

  // 세그먼트 OFF
  Pim.pth.byte = 0x00;
}

/***************************************************************/
/*  0~9 중에 하나의 수를 입력하면 그 값을 7-세그먼트에 출력한다.*/
/***************************************************************/
void set_7segment(unsigned int number) 
{
  switch (number) 
  {
    case 0 : 
        Pim.pth.byte = 0b00111111;		// 7-세그먼트 에서 '0'이 출력되도록 포트 값을 설정?
        break;  
    case 1 : 
        Pim.pth.byte = 0b00000110;		// 7-세그먼트 에서 '1'이 출력되도록 포트 값을 설정?
        break;
    case 2 : 
        Pim.pth.byte = 0b01011011;		// 7-세그먼트 에서 '2'가 출력되도록 포트 값을 설정?
        break;
    case 3 : 
        Pim.pth.byte = 0b01001111;		// 7-세그먼트 에서 '3'이 출력되도록 포트 값을 설정?
        break;
    case 4 : 
        Pim.pth.byte = 0b01100110;		// 7-세그먼트 에서 '4'가 출력되도록 포트 값을 설정?
        break;
    case 5 : 
        Pim.pth.byte = 0b01101101;		// 7-세그먼트 에서 '5'가 출력되도록 포트 값을 설정?
        break;
    case 6 : 
        Pim.pth.byte = 0b01111101;		// 7-세그먼트 에서 '6'이 출력되도록 포트 값을 설정?
        break;
    case 7 : 
        Pim.pth.byte = 0b00100111;		// 7-세그먼트 에서 '7'이 출력되도록 포트 값을 설정?
        break;
    case 8 : 
        Pim.pth.byte = 0b01111111;		// 7-세그먼트 에서 '8'이 출력되도록 포트 값을 설정?
        break;                                        
    case 9 : 
        Pim.pth.byte = 0b01101111;		// 7-세그먼트 에서 '9'가 출력되도록 포트 값을 설정?
        break;
    case 10 :
        Pim.pth.byte = 0b11111111;      // DP를 포함한 모든 세그먼트가 켜짐.
    default:
      break;
  }
  return;
}
