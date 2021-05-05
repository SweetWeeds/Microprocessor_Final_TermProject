/* queue.h */

#ifndef QUEUE_H
#define QUEUE_H

#include "dataframe.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct _Node {
	struct _Node* preNode;
	struct _Node* nextNode;
	struct _DataFrame* df;
} Node;

//typedef struct _Node Node;

void QueuePush(struct _DataFrame* df);
struct _DataFrame* QueuePop();
struct _DataFrame* QueueFront();

#endif /* QUEUE_H */

/* queue.h */
