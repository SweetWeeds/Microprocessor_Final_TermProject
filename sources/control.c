#include "control.h"

extern u32 TargetFloor;
extern u32 CurrentFloor;
extern u8 floor_buffer[9];
extern u32 fb_idx;
extern u8 TX[];

void STATE_CONTROL(DataFrame* df) {
    if (df->cmdnum == CMD_STATE_CTRL_FLOOR && df->data[0] <= '3' && '1' <= df->data[0]) {
        // 층 수 변경
        TargetFloor = CurrentFloor = (df->data[0] - '0') * 1000;
        set_7segment(df->data[0] - '0');
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
    u32 deleted_qsize;
    if (df->cmdnum == CMD_BUFFER_CTRL_ADD) {
        // 버퍼 추가
        QueueFloorPush((df->data[0] - '0') * 1000);
    }
    else if (df->cmdnum == CMD_BUFFER_CTRL_PRINT) {
        sprintf(TX, "<021025%d%-8s>", fb_idx, floor_buffer);
        write_sci0(TX);
    }
    else if (df->cmdnum == CMD_BUFFER_CTRL_CLR) {
        // 버퍼 비우기
        deleted_qsize = QueueFloorClear();
        while (deleted_qsize) {
            fb_idx -= deleted_qsize;
            floor_buffer[fb_idx] = 0;
        }
        //write_sci0("lcd_s");
        write_string(0x00, floor_buffer);
        //write_sci0("lcd_e");
    }
}
