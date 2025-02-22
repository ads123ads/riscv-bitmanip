#include "compliance_test.h"
#include "compliance_io.h"
#include "test_macros.h"

RV_COMPLIANCE_RV32M

RV_COMPLIANCE_CODE_BEGIN
    la a1,test_results
    li a2, 0x522a1063
    sbinvi t0,a2,3
    sw t0,0(a1)
    li a5, 0x8a671b8c
    sbinvi t2,a5,5
    sw t2,4(a1)
    li a3, 0x02eb0801
    sbinvi s5,a3,17
    sw s5,8(a1)
    li s3, 0x43737b61
    sbinvi s7,s3,24
    sw s7,12(a1)
    li s3, 0xf20d8a82
    sbinvi a4,s3,25
    sw a4,16(a1)
    li s0, 0x9543c51a
    sbinvi a3,s0,31
    sw a3,20(a1)
    li t0, 0x1014c66e
    sbinvi s3,t0,12
    sw s3,24(a1)
    li s8, 0x1a3c3257
    sbinvi t6,s8,8
    sw t6,28(a1)
    li s0, 0x88061100
    sbinvi a6,s0,2
    sw a6,32(a1)
    li a7, 0xfebefbcc
    sbinvi s4,a7,22
    sw s4,36(a1)
    RV_COMPLIANCE_HALT
RV_COMPLIANCE_CODE_END

.data
RV_COMPLIANCE_DATA_BEGIN
test_results:
.fill 10,4,-1
RV_COMPLIANCE_DATA_END
