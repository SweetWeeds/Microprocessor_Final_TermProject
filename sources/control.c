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
    DataFrame *df_tmp = NULL;
    u32 deleted_qsize;
    u32 add_size;
    u32 idx;
    if (df->cmdnum == CMD_BUFFER_CTRL_ADD) {
        // 버퍼 추가
        QueueFloorPush((df->data[0] - '0') * 1000);
    }
    else if (df->cmdnum == CMD_BUFFER_CTRL_ADD_MULTI) {
        // 버퍼 여러개 추가
        add_size = df->data[0] - '0';
        for (idx = 1; idx <= add_size; idx++) {
            df_tmp = (DataFrame *)malloc(sizeof(DataFrame));
            df_tmp->groupnum = GROUP_BUFFER;
            df_tmp->cmdclass = CMD_CLASS_CONTROL;
            df_tmp->cmdnum = CMD_BUFFER_CTRL_ADD;
            df_tmp->dataformat = D1;
            df_tmp->data[0] = df->data[idx];
            QueuePush(df_tmp);
        }
    }
    else if (df->cmdnum == CMD_BUFFER_CTRL_PRINT) {
        // 정보 출력
        sprintf(TX, "<021025%d%-15s>", fb_idx, floor_buffer);
        write_sci0(TX);
    }
    else if (df->cmdnum == CMD_BUFFER_CTRL_DEL) {
        // 뒤에서 버퍼 하나를 제거
        if (fb_idx <= 1) return;
        QueueFloorDelete();
    }
}
