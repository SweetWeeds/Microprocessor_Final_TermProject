/* control.h */

#ifndef CONTROL_H
#define CONTROL_H

#include "dataframe.h"
#include "queue_floor.h"
#include "rti.h"
#include "lcd.h"
#include "sci.h"
#include "seven_seg.h"

void STATE_CONTROL(struct _DataFrame* df);
void PAUSE_CONTROL(struct _DataFrame* df);
void BUFFER_CONTROL(struct _DataFrame* df);

// 층수: 10ms 때마다 +-1씩 이동
#define FLOOR_ONE   1000   // 1층
#define FLOOR_TWO   2000   // 2층
#define FLOOR_THREE 3000   // 3층

#define ONE_TWO     12   // 1층 -> 2층
#define TWO_ONE     21   // 2층 -> 1층
#define TWO_THREE   23   // 2층 -> 3층
#define THREE_TWO   32   // 3층 -> 2층
#define THREE_ONE   31   // 3층 -> 1층
#define ONE_THREE   13   // 1층 -> 3층

#endif
