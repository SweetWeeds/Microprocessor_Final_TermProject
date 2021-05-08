/* dataframe.h */

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "exception.h"
//#include "lcd.h"

#define MAX_FRAME_SIZE  24	// �ִ� ������ ������ ũ��: 24����Ʈ
#define TIMEOUT_SIZE    MAX_FRAME_SIZE + 5  // Timtout ���� : �ִ� ������ ������ ũ�� + 5 �̻�
#define MAX_DATA_SIZE   16	// �ִ� ������ ũ��

// Data ũ��
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
#define CMD_STATE_CTRL_FLOOR   0  // ���� ����
#define CMD_STATE_UPDATE_PRINT 1  // ���� ���

#define CMD_PAUSE_CTRL_PAUSE   0  // �Ͻ�����

#define CMD_BUFFER_CTRL_ADD         0  // ���� �߰�
#define CMD_BUFFER_CTRL_ADD_MULTI   1  // ���� ������ �߰�
#define CMD_BUFFER_CTRL_PRINT       2  // ���� ���� ��� ��û
#define CMD_BUFFER_UPDATE_PRINT     3  // ���� ���� ���
#define CMD_BUFFER_CTRL_DEL         4  // ���� ����

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

// ������ ������
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
