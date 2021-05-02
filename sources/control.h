/* control.h */

#ifndef CONTROL_H
#define CONTROL_H

#include "dataframe.h"
#include "queue_floor.h"

void STATE_CONTROL(DataFrame* df);
void PAUSE_CONTROL(DataFrame* df);
void BUFFER_CONTROL(DataFrame* df);

// 모드 지정
#define FLOOR_ONE   100   // 1층
#define FLOOR_TWO   200   // 2층
#define FLOOR_THREE 300   // 3층

#define ONE_TWO     12   // 1층 -> 2층
#define TWO_ONE     21   // 2층 -> 1층
#define TWO_THREE   23   // 2층 -> 3층
#define THREE_TWO   32   // 3층 -> 2층
#define THREE_ONE   31   // 3층 -> 1층
#define ONE_THREE   13   // 1층 -> 3층

#endif