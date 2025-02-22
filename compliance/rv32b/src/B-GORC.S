#include "compliance_test.h"
#include "compliance_io.h"
#include "test_macros.h"

RV_COMPLIANCE_RV32M

RV_COMPLIANCE_CODE_BEGIN
    la a1,test_results
    li a7, 0x778bd1db
    li t4, 0xdef3c035
    gorc t6,a7,t4
    sw t6,0(a1)
    li t6, 0xffaace79
    li s1, 0x11e15d6b
    gorc s3,t6,s1
    sw s3,4(a1)
    li a6, 0x04bc5eac
    li t2, 0x33397f4e
    gorc t0,a6,t2
    sw t0,8(a1)
    li a4, 0x40ee4840
    li s8, 0x18331b85
    gorc t4,a4,s8
    sw t4,12(a1)
    li t6, 0x5a0d8ae2
    li a7, 0xfaafb8a6
    gorc s2,t6,a7
    sw s2,16(a1)
    li a4, 0xcccb9502
    li s0, 0xde163e74
    gorc s9,a4,s0
    sw s9,20(a1)
    li s4, 0x00002000
    li s5, 0x40f01f17
    gorc t0,s4,s5
    sw t0,24(a1)
    li s2, 0x00120210
    li s8, 0xc6fe507a
    gorc t1,s2,s8
    sw t1,28(a1)
    li s11, 0x00200900
    li t1, 0xf9fceffe
    gorc s4,s11,t1
    sw s4,32(a1)
    li a7, 0x002c80c0
    li s2, 0xe2d30092
    gorc s3,a7,s2
    sw s3,36(a1)
    li s5, 0x04000018
    li a3, 0x2d4792d3
    gorc a5,s5,a3
    sw a5,40(a1)
    li s11, 0x08c03000
    li a3, 0x3fef8b13
    gorc a4,s11,a3
    sw a4,44(a1)
    li t3, 0x0e030000
    li a2, 0x0000000b
    gorc s0,t3,a2
    sw s0,48(a1)
    li a3, 0x80031100
    li t3, 0xefea7d18
    gorc a7,a3,t3
    sw a7,52(a1)
    li s10, 0x82200401
    li t0, 0x821d8858
    gorc a0,s10,t0
    sw a0,56(a1)
    li t1, 0xc480e100
    li t4, 0x4480874c
    gorc a7,t1,t4
    sw a7,60(a1)
    RV_COMPLIANCE_HALT
RV_COMPLIANCE_CODE_END

.data
RV_COMPLIANCE_DATA_BEGIN
test_results:
.fill 16,4,-1
RV_COMPLIANCE_DATA_END
