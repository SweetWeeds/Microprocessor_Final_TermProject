#include "exception.h"
extern u8 TX[];

// ����ó��
void ExceptionHandling(unsigned int ec) {
    sprintf(TX, "<050000%d>", ec);
    write_sci0(TX);
}
