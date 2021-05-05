#include "main.h"

u32 TargetFloor = FLOOR_ONE;	    // 가고자 하는 층
u32 CurrentFloor = FLOOR_ONE;	    // 현재 층 (1층: 1000, 1~2층 사이: 1001~1999 ...)
u32 tmpFloor = FLOOR_ONE;           // 버퍼의 값을 임시 저장
u8 isMoving = FALSE;                // 플래그: 움직이고 있는가?
DataFrame* df = NULL;               // 큐 데이터 프레임
u8 RX[RX_BUFFER_SIZE] = { 0, };     // 시리얼 수신 버퍼
u8 TX[TX_BUFFER_SIZE] = { 0, };     // 시리얼 송신 버퍼
u8 LCD_FIRST_LINE[LCD_BUFFER_SIZE];     // LCD 버퍼 첫번째 줄
u8 LCD_SECOND_LINE[LCD_BUFFER_SIZE];    // LCD 버퍼 두번째 줄
u32 tmp_pwm_period = LOW_SPEED;
u32 pwm_period = LOW_SPEED;	// 모터 주기

void main() {
    u32 pwm_period_offset = 0;          // pwm 속도 오프셋 (ATD를 통한 속도 제어)
    u32 pre_pwm_period_offset = 1;
    u8 atd_val = 0;

    // 인터럽트 초기화
    int_disable();
    ini_interrupt();
    init_rti();
    int_enable();
    xint_enable();

    // 시리얼 초기화
    init_sci0(19200, RX);
    write_sci0("SCI OK");

    // LED 초기화
    init_led();
    set_door(0); // 닫힌 상태

    // ATD 초기화
    init_atd0();

    // 세븐 세그먼트 초기화
    init_seven_seg();
    set_7segment(CurrentFloor / 1000);

    // LCD 초기화
    init_LCD();

    // DataFrame 테이블 초기화
    InitFormatTable();

    //Insert Application Software Here.
    for (;;) {
        // ATD
        pwm_period_offset = convert_value(get_atd0(ANALOG_INPUT_CHANNEL));
        // pwm 오프셋 반영
        pwm_period = tmp_pwm_period + (tmp_pwm_period & 1) - pwm_period_offset;
        if (pre_pwm_period_offset != pwm_period_offset) {
            pre_pwm_period_offset = pwm_period_offset;
            sprintf(LCD_SECOND_LINE, "%d", pwm_period);
            write_string(0x40, LCD_SECOND_LINE);
        }

        // 현재 상태 체크
        if (!isMoving) {
            // 정지 중
            tmpFloor = QueueFloorPop();
            if (tmpFloor != 0 && tmpFloor != CurrentFloor) {
                TargetFloor = tmpFloor;
                isMoving = TRUE;
            }
        }

        // 큐에서 데이터 읽어오기
        df = QueuePop();
        // 널 포인터 체크
        if (df) {
            // 명령어 처리
            switch (df->groupnum) {
                case GROUP_STATE:
                    STATE_CONTROL(df);
                    break;
                case GROUP_PAUSE:
                    PAUSE_CONTROL(df);
                    break;
                case GROUP_BUFFER:
                    BUFFER_CONTROL(df);
                    break;
            }
            free(df);
            df = NULL;
        }
    }
}
