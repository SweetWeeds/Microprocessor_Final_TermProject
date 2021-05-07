/* queue.h */

#ifndef QUEUE_H
#define QUEUE_H

#include "stdio.h"
#include "stdlib.h"
//#include "exception.h"
#include "dataframe.h"

struct _Node {
	struct _DataFrame* df;
	struct _Node* preNode;
	struct _Node* nextNode;
};

typedef struct _Node Node;

void QueuePush(struct _DataFrame* df);
struct _DataFrame* QueuePop();
struct _DataFrame* QueueFront();

#endif /* QUEUE_H */

/* queue.h */
