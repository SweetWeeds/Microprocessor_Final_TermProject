/* queue_floor.h */

#ifndef QUEUE_FLOOR_H
#define QUEUE_FLOOR_H

#include "stdio.h"
#include "stdlib.h"
#include "dataframe.h"

typedef unsigned int u32;

typedef struct _FloorNode {
	u32 data;
	struct _FloorNode* preNode;
	struct _FloorNode* nextNode;
} FloorNode;

//typedef struct _FloorNode FloorNode;

void QueueFloorClear();
void QueueFloorPush(u32 data);
u32 QueueFloorPop();
u32 QueueFloorFront();

#endif /* QUEUE_FLOOR_H */

/* queue_floor.h */
