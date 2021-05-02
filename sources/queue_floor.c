/* queue.c */

#include "queue_floor.h"

FloorNode* Head = NULL;
FloorNode* Tail = NULL;

void QueueFloorPush(u32 data) {
	FloorNode* newNode = (FloorNode*)malloc(sizeof(Node));
	// 동적할당 실패 체크
	if (newNode == NULL) {
		//ExceptionHandling(DynamicAllocFailed);
		return;
	}
	newNode->data = data;
	// 큐가 빈 경우
	if (Head == NULL && Tail == NULL) {
		// 동적할당 성공 체크
		Head = newNode;
		Head->preNode = NULL;
		Head->nextNode = NULL;
		Tail = Head;
	}
	// 큐가 비어있지 않은 경우
	else if (Head != NULL && Tail != NULL) {
		newNode->preNode = Tail;
		newNode->nextNode = NULL;
		Tail->nextNode = newNode;
		Tail = newNode;
	}
	// 예외 처리 (잘못된 핸들링)
	else {
		//ExceptionHandling(QueueFault);
        return;
	}
}

u32 QueueFloorPop() {
	// 헤드가 비어있지 않은 경우
	if (Head != NULL) {
		FloorNode* tmpNode = Head;
		u32 data = tmpNode->data;
		// 헤드와 테일이 일치 (남은 노드가 하나)
		if (Head == Tail) {
			Head = NULL;
			Tail = NULL;
		}
		// 헤드 != 테일 : 남은 노드가 2개 이상
		else {
			Head = Head->nextNode;
			Head->preNode = NULL;
		}
		free(tmpNode);
		return data;
	}
	// 헤드가 빈 경우
	else {
		return 0;
	}
}

// 큐 앞 조회
u32 QueueFloorFront() {
	// 헤드가 비어있지 않은 경우
	if (Head != NULL) {
		return Head->data;
	}
	// 헤드가 빈 경우
	else {
		return NULL;
	}
}

/* queue_floor.c */
