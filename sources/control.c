#include "control.h"

extern char CurrentMode;

void STATE_CONTROL(DataFrame* df) {
    if (df->cmdnum == CMD_STATE_CTRL_FLOOR && df->data[0] <= '3' && '1' <= df->data[0]) {
        // 층 수 변경
        CurrentMode = df->data[0] - '0';
    }
    else if (df->cmdnum == CMD_STATE_UPDATE_PRINT) {

    }
}

void PAUSE_CONTROL(DataFrame* df) {
    u8 data = df->data[0];
    if (df->cmdnum == CMD_PAUSE_CTRL_PAUSE) {
        if (data == '0') {
            // 시작
        }
        else if (data == '1') {
            // 일시정지
        }
    }
}

void BUFFER_CONTROL(DataFrame* df) {
    if (df->cmdnum == CMD_BUFFER_CTRL_ADD) {
        // 버퍼 추가
        FloorQueuePush((df->data[0] - '0') * 1000);
    }
    else if (df->cmdnum == CMD_BUFFER_CTRL_CLR) {
        // 버퍼 비우기
        FloorQueueClear();
    }
    else if (df->cmdnum == CMD_BUFFER_UPDATE_PRINT) {
        // 버퍼 정보 출력

    }
}
