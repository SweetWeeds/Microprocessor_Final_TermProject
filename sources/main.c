#include "main.h"

u8 CurrentMode = FLOOR_ONE;
DataFrame* df = NULL;
unsigned char RX[RX_BUFFER_SIZE];

void main() {
    // 인터럽트 초기화
    int_disable();
    ini_interrupt();
    int_enable();
    xint_enable();

    // 시리얼 초기화
    init_sci0(19200, RX);
    write_sci0("SCI OK");

    // LED 초기화
    init_led();

    // ATD 초기화
    init_atd0();

    // PWM 초기화
    init_pwm();

    // 세븐 세그먼트 초기화
    init_seven_seg();

    // LCD 초기화
    init_LCD();
    //write_string(0x00, "Init Complete");

    // DataFrame 테이블 초기화
    InitFormatTable();


	//Insert Application Software Here.
	for (;;) {
        // 현재 상태 체크
        if (CurrentMode >= ONE_TWO) {
            // 이동 중

        }
        else {

        }

        // 큐에서 데이터 읽어오기
        df = QueuePop();
        // 널 포인터 체크
        if (df) {
            //set_inst_register(CODE_CLR_DISP);
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