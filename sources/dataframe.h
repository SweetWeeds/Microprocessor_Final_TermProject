/* dataframe.h */

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "exception.h"
//#include "lcd.h"

#define MAX_FRAME_SIZE  24	// 최대 데이터 프레임 크기: 24바이트
#define TIMEOUT_SIZE    MAX_FRAME_SIZE + 5  // Timtout 기준 : 최대 데이터 프레임 크기 + 5 이상
#define MAX_DATA_SIZE   16	// 최대 데이터 크기

// Data 크기
#define D1  0
#define D2  1
#define D3  2
#define D4  3
#define D8  4
#define D10 5
#define D16 6

// Group No
#define GROUP_STATE	  0x00
#define GROUP_PAUSE   0x01
#define GROUP_BUFFER  0x02

// CMD Class
#define CMD_CLASS_CONTROL 0x00  // PC -> MCU
#define CMD_CLASS_UPDATE  0x01  // MCU -> PC

// CMD Num
#define CMD_STATE_CTRL_FLOOR   0  // 층수 변경
#define CMD_STATE_UPDATE_PRINT 1  // 상태 출력

#define CMD_PAUSE_CTRL_PAUSE   0  // 일시정지

#define CMD_BUFFER_CTRL_ADD         0  // 버퍼 추가
#define CMD_BUFFER_CTRL_ADD_MULTI   1  // 버퍼 여러개 추가
#define CMD_BUFFER_CTRL_PRINT       2  // 버퍼 정보 출력 요청
#define CMD_BUFFER_UPDATE_PRINT     3  // 버퍼 정보 출력
#define CMD_BUFFER_CTRL_DEL         4  // 버퍼 비우기

#define ETX_VALID_BIT 0x00

// Data Format
#define BYTE_FORMAT_D1    0
#define BYTE_FORMAT_D2    1
#define BYTE_FORMAT_D3    2
#define BYTE_FORMAT_D4    3
#define BYTE_FORMAT_D8    4
#define BYTE_FORMAT_D10   5
#define BYTE_FORMAT_D16   6

typedef unsigned char  u8;		// 1 Byte
typedef unsigned short u16;		// 2 Byte
typedef unsigned int   u32;		// 4 Byte

// 데이터 프레임
typedef struct {
	u16 groupnum;
	u16 cmdclass;
	u16 cmdnum;
	u16 dataformat;
	u8 data[MAX_DATA_SIZE + 6];
} DataFrame;

//typedef struct _DataFrame DataFrame;

/* Function Prototypes */
void InitFormatTable();
DataFrame* GetDataFrame(const u8*);
unsigned int DataCheck(u8*, u8);
/* Function Prototypes */

#endif /* DATAFRAME_H */

/* dataframe.h */
