#include "control.h"

extern u32 CurrentFloor;
extern u8 floor_buffer[9];
extern u32 fb_idx;
extern u8 TX[];

void STATE_CONTROL(DataFrame* df) {
    if (df->cmdnum == CMD_STATE_CTRL_FLOOR && df->data[0] <= '3' && '1' <= df->data[0]) {
        // 층 수 변경
        CurrentFloor = (df->data[0] - '0') * 1000;
    }
}

void PAUSE_CONTROL(DataFrame* df) {
    u8 data = df->data[0];
    if (df->cmdnum == CMD_PAUSE_CTRL_PAUSE) {
        if (data == '0') {
            // 시작
            rti_enable();
            pwm_enable();
        }
        else if (data == '1') {
            // 일시정지
            rti_disable();
            pwm_disable();
        }
    }
}

void BUFFER_CONTROL(DataFrame* df) {
    if (df->cmdnum == CMD_BUFFER_CTRL_ADD) {
        // 버퍼 추가
        QueueFloorPush((df->data[0] - '0') * 1000);
    }
    else if (df->cmdnum == CMD_BUFFER_CTRL_CLR) {
        // 버퍼 비우기
        QueueFloorClear();
    }
}
