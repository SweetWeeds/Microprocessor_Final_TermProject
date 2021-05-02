#include <stdio.h>
#include "queue.h"
#include "dataframe.h"

//const u8 BYTE_SIZE_TYPE[6] = { 1, 2, 3, 4, 10, 16 };    // Byte Format 값 당 Byte size

extern const u8 BYTE_SIZE_TYPE[6];

void printDF(DataFrame *df) {
	// Group
	switch (df->groupnum) {
	case GROUP_LED:
		printf("GROUP: LED, ");
		switch (df->cmdnum) {
		case CMD_LED_CTRL_ON_SEL:
			printf("CMD NUM: CMD_LED_CTRL_ON_SEL, ");
			break;
		case CMD_LED_CTRL_DEC:
			printf("CMD NUM: CMD_LED_CTRL_DEC, ");
			break;
		case CMD_LED_CTRL_HEX:
			printf("CMD NUM: CMD_LED_CTRL_HEX, ");
			break;
		case CMD_LED_CTRL_BIN:
			printf("CMD NUM: CMD_LED_CTRL_BIN, ");
			break;
		case CMD_LED_CTRL_OFF_SEL:
			printf("CMD NUM: CMD_LED_CTRL_OFF_SEL, ");
			break;
		}
		break;
	case GROUP_SEG:
		printf("GROUP: SEVEN_SEG, ");
		if (df->cmdnum == CMD_SEG_UPDATE_LED_CNT)
			printf("CMD NUM: CMD_SEG_UPDATE_LED_CNT, ");
		break;
	case GROUP_SWITCH:
		printf("GROUP: SWITCH, ");
		if (df->cmdnum == CMD_SWITCH_UPDATE_STAT)
			printf("CMD NUM: CMD_SWITCH_UPDATE_STAT, ");
		break;
	case GROUP_LCD:
		printf("GROUP: LCD, ");
		if (df->cmdnum == CMD_LCD_CTRL_HIGH)
			printf("CMD NUM: CMD_LCD_CTRL_LOW, ");
		else if (df->cmdnum == CMD_LCD_CTRL_LOW)
			printf("CMD NUM: CMD_LCD_CTRL_LOW, ");
		break;
	case GROUP_ADC:
		printf("GROUP: ADC, ");
		if (df->cmdnum == CMD_ADC_UPDATE)
			printf("CMD NUM: CMD_ADC_UPDATE, ");
		break;
	case GROUP_SYS:
		printf("GROUP: SYS, ");
		if (df->cmdnum == CMD_SYS_UPDATE) {
			printf("CMD NUM: CMD_SYS_UPDATE, ");
		}
		break;
	}
	// CMD class
	switch (df->cmdclass) {
	case CMD_CLASS_CONTROL:
		printf("CMD CLASS: CTRL, ");
		break;
	case CMD_CLASS_UPDATE:
		printf("CMD CLASS: UPDATE, ");
		break;
	}
	// TEXT FORMAT
	printf("TEXT FORMAT: %d(%d), ", df->dataformat, BYTE_SIZE_TYPE[df->dataformat]);
	// DATA
	printf("DATA: %s\n", df->data);
}

int main() {
	InitFormatTable();
	char buf[29] = { 0, };

	for (int i = 0; i < 82; i++) {
		scanf("%s", buf);
		DataFrame* df = GetDataFrame(buf);
		Push(df);
	}
	for (int i = 0; i < 100; i++) {
		DataFrame* df = Pop();
		if (df) {
			printDF(df);
			free(df);
		}
		else {
			printf("EMPTY!\n");
		}
	}

	return 0;
}
