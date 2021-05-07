/* queue_floor.h */

#ifndef QUEUE_FLOOR_H
#define QUEUE_FLOOR_H

#include "stdio.h"
#include "stdlib.h"
#include "lcd.h"

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct _FloorNode {
	u32 data;
	struct _FloorNode* preNode;
	struct _FloorNode* nextNode;
} FloorNode;

//typedef struct _FloorNode FloorNode;

u32 QueueFloorClear();
void QueueFloorPush(u32 data);
u32 QueueFloorPop();
u32 QueueFloorFront();
u32 QueueFloorEnd();
#endif /* QUEUE_FLOOR_H */

/* queue_floor.h */
