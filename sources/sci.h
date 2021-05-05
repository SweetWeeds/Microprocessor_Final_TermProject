#ifndef SCI_H        /*prevent duplicated includes*/
#define SCI_H


/*Includes*/
#include "projectglobals.h"

#define RX_BUFFER_SIZE 30
#define TX_BUFFER_SIZE 20
#define SCICR1_INIT_DEFAULT 0x00
#define SCICR2_INIT_DEFAULT 0x2c
#define TIE_ENABLE 0x80
#define TE_ENABLE 0x08

void init_sci0(int, unsigned char *);
void write_sci0(unsigned char *text);
void sci0_handler(void);


#endif /*SCI_H*/