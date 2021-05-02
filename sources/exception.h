#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "stdio.h"
#include "stdlib.h"
#include "sci.h"

// 에러코드 정의
#define OverDataSize  0
#define LossDataSize  1
#define OverGroupCnt  2
#define OverClassCnt  3
#define OverFormatCnt 4
#define CantFindCmd_STATE 5
#define CantFindCmd_PAUSE 6
#define CantFindCmd_BUFFER 7
#define Timeout 8
#define Normal  9

// 예외처리
void ExceptionHandling(unsigned int ec);

#endif	/* EXCEPTION_H */
