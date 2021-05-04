#include "control.h"

extern unsigned char floor_buffer[9];
extern u32 fb_idx;
u8 sci_buffer[15] = { 0, };

void STATE_CONTROL(DataFrame* df) {
    if (df->cmdnum == CMD_STATE_CTRL_FLOOR && df->data[0] <= '3' && '1' <= df->data[0]) {
        // 층 수 변경
        CurrentMode = (df->data[0] - '0') * 1000;
    }
    else if (df->cmdnum == CMD_STATE_UPDATE_PRINT) {
        // 층 수 출력
        sprintf(sci_buffer, "<%c>", df->data[0]);
        write_sci0(sci_buffer);
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
    else if (df->cmdnum == CMD_BUFFER_UPDATE_PRINT) {
        // 버퍼 정보 출력
        sprintf(sci_buffer, "<%1d%s>", fb_idx, floor_buffer);
        write_sci0(sci_buffer);
    }
}
