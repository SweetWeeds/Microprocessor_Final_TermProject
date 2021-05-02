/* queue.h */

#ifndef QUEUE_H
#define QUEUE_H

#include "stdio.h"
#include "stdlib.h"
//#include "exception.h"
#include "dataframe.h"

struct _Node {
	DataFrame* df;
	struct _Node* preNode;
	struct _Node* nextNode;
};

typedef struct _Node Node;

void QueuePush(DataFrame* df);
DataFrame* QueuePop();
DataFrame* QueueFront();

#endif /* QUEUE_H */

/* queue.h */
