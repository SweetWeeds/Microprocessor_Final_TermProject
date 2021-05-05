#include "exception.h"
extern u8 TX[];

// 예외처리
void ExceptionHandling(unsigned int ec) {
    sprintf(TX, "<050000%d>", ec);
    write_sci0(TX);
}
