#include "interrupt.h"

extern unsigned int led_digit;
extern unsigned char CurrentMode;
unsigned char buf[27];

/*************************************************/
/*  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�.   */
/*************************************************/
void ini_interrupt(void){
    Pim.ddrj.byte = 0b00000000;   // ���ͷ�Ʈ ��Ʈ�� ���� ���� 
    Pim.piej.byte = 0xff;		    // ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
    Pim.ppsj.byte = 0x00;		    // ���ͷ�Ʈ ��Ʈ�� ���� ���� (0x00: �ϰ�����, 0xff: ��¿���)  
}


/***********************************
 *  SW2�� ������ Bar LED ��ü ����  *
 *  SW3�� ������ Bar LED ��ü �ҵ�  *
 ***********************************/

void interruptJ_function(void)
{
    DataFrame* df = NULL;
    //unsigned char atd_value;
    if(Pim.pifj.byte & SW2_MASK_BIT)      // SW2�� ���ͷ�Ʈ �߻� (GUI ī���� ���)
    { 
        QueueFloorPush(2000);
        Pim.pifj.byte |= SW2_MASK_BIT;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    }
    else if(Pim.pifj.byte & SW3_MASK_BIT)  // SW3�� ���ͷ�Ʈ �߻� (ADC �� ����)
    {
        QueueFloorPush(3000);
        Pim.pifj.byte |= SW3_MASK_BIT;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    }
    df = NULL;
}

/***********************************
 *  SW1�� ������ LED ���� ����      *
 ***********************************/
void interruptX_function (void)    //XIRQ interrupt ���� �Լ� (SW1�� ���ͷ�Ʈ �߻�)
{
    QueueFloorPush(1000);
}