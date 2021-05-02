#include "atd.h"
/*****************************************************/
/*  ATD 모듈을 초기화 한다.                           */
/*****************************************************/

void init_atd0(void) {

    Atd0.atdctl2.byte = ATDCTL2_INIT;   // ADPU: Power Up
    Atd0.atdctl3.byte = ATDCTL3_INIT;   // Conversion Sequence Length = 2, FIFO off, Backgroud Debug freeze: Continue conversion
    Atd0.atdctl4.byte = ATDCTL4_INIT;   // A/D resolution 10bit, Sample time 16 A/D conversion clock period
                                        // Clock prescale value: (divided by 28)
    Atd0.atdctl5.byte = ATDCTL5_INIT;   // Right justification, Unsigned, Continuous Scan, Multi-Channel off, AN0 
}

/******************************************************/
/*  입력 받은 채널에 해당하는 ATD 변환 값을 반환한다.    */
/******************************************************/
int get_atd0(int channel) 
{ 
   
    Atd0.atdctl5.byte |= SCF_SET;            //Write to ATDCTL5 (a new conversion sequence is started)
 
    if (channel >= 0 && channel <= 7) {     // Check channel range
        return (int)(Atd0.atddr[0].d10);      // return ATD result register data
    }
    else return -1;                                  // Invalid channel
}

unsigned char convert_value(int cnt)
{
    // VR_FOUR를 기준으로 분할
    if (cnt < VR_FOUR) {
        // 출력 : 0
        if (cnt < VR_ZERO) {
            return 0;
        }
        // 출력 : 1
        else if (cnt < VR_ONE) {
            return 1;
        }
        // 출력 : 2
        else if (cnt < VR_TWO) {
            return 2;
        }
        // 출력 : 3
        else if (cnt < VR_THREE) {
            return 3;
        }
        // 출력 : 4
        else {
            return 4;
        }
    // 551보다 큰 경우
    } else {
        // 출력 : 5
        if (cnt < VR_FIVE) {
            return 5;
        }
        // 출력 : 6
        else if (cnt < VR_SIX) {
            return 6;
        }
        // 출력 : 7
        else if (cnt < VR_SEVEN) {
            return 7;
        }
        // 출력 : 8
        else if (cnt < VR_EIGHT) {
            return 8;
        }
        // 출력 : 9
        else {
            return 9;
        }
    }
    return 0;   // 예외 처리
}
