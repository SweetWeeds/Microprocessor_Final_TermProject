/* queue_floor.h */

#ifndef QUEUE_FLOOR_H
#define QUEUE_FLOOR_H

#include "stdio.h"
#include "stdlib.h"
#include "dataframe.h"

typedef unsigned int u32;

struct _FloorNode {
	u32 data;
	struct _FloorNode* preNode;
	struct _FloorNode* nextNode;
};

typedef struct _FloorNode FloorNode;

void FloorQueuePush(u32 data);
u32 FloorQueuePop();
u32 FloorQueueFront();
void FloorQueueClear();

#endif /* QUEUE_FLOOR_H */

/* queue_floor.h */
