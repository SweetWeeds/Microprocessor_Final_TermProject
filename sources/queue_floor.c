/* queue.c */

#include "queue_floor.h"

FloorNode* HeadFloor = NULL;
FloorNode* TailFloor = NULL;

void QueueFloorPush(u32 data) {
	FloorNode* newNode = (FloorNode*)malloc(sizeof(FloorNode));
	// 동적할당 실패 체크
	if (newNode == NULL) {
		//ExceptionHandling(DynamicAllocFailed);
		return;
	}
	newNode->data = data;
	// 큐가 빈 경우
	if (HeadFloor == NULL && TailFloor == NULL) {
		// 동적할당 성공 체크
		HeadFloor = newNode;
		HeadFloor->preNode = NULL;
		HeadFloor->nextNode = NULL;
		TailFloor = HeadFloor;
	}
	// 큐가 비어있지 않은 경우
	else if (HeadFloor != NULL && TailFloor != NULL) {
		newNode->preNode = TailFloor;
		newNode->nextNode = NULL;
		TailFloor->nextNode = newNode;
		TailFloor = newNode;
	}
	// 예외 처리 (잘못된 핸들링)
	else {
		//ExceptionHandling(QueueFault);
        return;
	}
}

u32 QueueFloorPop() {
	// 헤드가 비어있지 않은 경우
	if (HeadFloor != NULL) {
		FloorNode* tmpNode = HeadFloor;
		u32 data = tmpNode->data;
		// 헤드와 테일이 일치 (남은 노드가 하나)
		if (HeadFloor == TailFloor) {
			HeadFloor = NULL;
			TailFloor = NULL;
		}
		// 헤드 != 테일 : 남은 노드가 2개 이상
		else {
			HeadFloor = HeadFloor->nextNode;
			HeadFloor->preNode = NULL;
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
	if (HeadFloor != NULL) {
		return HeadFloor->data;
	}
	// 헤드가 빈 경우
	else {
		return 0;
	}
}

/* queue_floor.c */
