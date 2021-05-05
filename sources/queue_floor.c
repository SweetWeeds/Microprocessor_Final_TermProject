/* queue.c */

#include "queue_floor.h"

FloorNode* HeadFloor = NULL;
FloorNode* TailFloor = NULL;
u8 floor_buffer[10] = { 0, };
u32 fb_idx = 0;
extern u8 LCD_FIRST_LINE[];     // LCD 버퍼 첫번째 줄
extern u32 CurrentFloor;
extern u32 TargetFloor;
extern u8 isMoving;

void QueueFloorClear() {
	while (HeadFloor != NULL) {
		QueueFloorPop();
	}
}

void QueueFloorPush(u32 data) {
	FloorNode* newNode = NULL;
    /*********************** 예외 처리 ***********************/
    // 맨 마지막에 입력되었던 값과 일치 시 큐를 입력하지 않음.
    if (QueueFloorEnd() == data || fb_idx > 8) return;
    // 움직이지 않을때: 현재 층은 입력 X
    if (!isMoving && CurrentFloor == data) return;
    // 큐가 빈 경우: 목표로 하는 곳은 입력 X
    if (HeadFloor == NULL && TargetFloor == data) return;
	newNode = (FloorNode*)malloc(sizeof(FloorNode));
    /********************************************************/

    // floor_buffer 입력
    floor_buffer[fb_idx++] = (data / 1000) + '0';
    floor_buffer[fb_idx] = 0;
    sprintf(LCD_FIRST_LINE, "%-16s", floor_buffer);
    write_string(0x00, LCD_FIRST_LINE);
	
    // 동적할당 실패 체크
	if (newNode == NULL) {
        //write_sci0("DA_Failed");
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
        //write_sci0("Handling_Fault");
        return;
	}
}

u32 QueueFloorPop() {
    u32 idx = 0;
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

// 큐 끝 조회
u32 QueueFloorEnd() {
    if (TailFloor != NULL) {
        return TailFloor->data;
    }
    else {
        return 0;
    }
}

/* queue_floor.c */
