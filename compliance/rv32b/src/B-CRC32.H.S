#include "compliance_test.h"
#include "compliance_io.h"
#include "test_macros.h"

RV_COMPLIANCE_RV32M

RV_COMPLIANCE_CODE_BEGIN
    la a1,test_results
    li s4, 0xd77b6ecd
    crc32.h s6,s4
    sw s6,0(a1)
    li s1, 0x36a9a6d7
    crc32.h t5,s1
    sw t5,4(a1)
    li s11, 0x219954ae
    crc32.h a3,s11
    sw a3,8(a1)
    li t2, 0x91f3a75b
    crc32.h a6,t2
    sw a6,12(a1)
    li s5, 0x6723f89c
    crc32.h t5,s5
    sw t5,16(a1)
    li s4, 0x6042e65d
    crc32.h a2,s4
    sw a2,20(a1)
    li s2, 0x00000000
    crc32.h t6,s2
    sw t6,24(a1)
    li t3, 0x00000004
    crc32.h s10,t3
    sw s10,28(a1)
    li a7, 0x0000002d
    crc32.h s10,a7
    sw s10,32(a1)
    li t4, 0x00000a80
    crc32.h s9,t4
    sw s9,36(a1)
    li s6, 0x00000dd7
    crc32.h s0,s6
    sw s0,40(a1)
    li a0, 0x00156892
    crc32.h s3,a0
    sw s3,44(a1)
    li s11, 0x0020aa01
    crc32.h s10,s11
    sw s10,48(a1)
    li a0, 0x002f74a0
    crc32.h a7,a0
    sw a7,52(a1)
    li t2, 0x00f03303
    crc32.h t1,t2
    sw t1,56(a1)
    li s9, 0x020010d3
    crc32.h t3,s9
    sw t3,60(a1)
    li a3, 0x020010db
    crc32.h a6,a3
    sw a6,64(a1)
    li a2, 0x04000004
    crc32.h s4,a2
    sw s4,68(a1)
    li s10, 0x06652557
    crc32.h s0,s10
    sw s0,72(a1)
    li a4, 0x06807dd5
    crc32.h s11,a4
    sw s11,76(a1)
    li s9, 0x08000ef5
    crc32.h a2,s9
    sw a2,80(a1)
    li a6, 0x08015886
    crc32.h a0,a6
    sw a0,84(a1)
    li t5, 0x0806a022
    crc32.h s0,t5
    sw s0,88(a1)
    li s7, 0x0810691e
    crc32.h s0,s7
    sw s0,92(a1)
    li s1, 0x10080084
    crc32.h t1,s1
    sw t1,96(a1)
    li t1, 0x1c48c7c4
    crc32.h s9,t1
    sw s9,100(a1)
    li s7, 0x27f33a8a
    crc32.h a4,s7
    sw a4,104(a1)
    li s10, 0x28083074
    crc32.h a7,s10
    sw a7,108(a1)
    li t0, 0x29a94208
    crc32.h s7,t0
    sw s7,112(a1)
    li s10, 0x42050184
    crc32.h s2,s10
    sw s2,116(a1)
    li s0, 0x561a6628
    crc32.h s6,s0
    sw s6,120(a1)
    li s5, 0x5ffbac3e
    crc32.h t2,s5
    sw t2,124(a1)
    li t1, 0x72a10106
    crc32.h a2,t1
    sw a2,128(a1)
    li s10, 0x809ffe48
    crc32.h s2,s10
    sw s2,132(a1)
    li t5, 0x80a27fee
    crc32.h t4,t5
    sw t4,136(a1)
    li s9, 0x820417c0
    crc32.h s11,s9
    sw s11,140(a1)
    li t0, 0xa9000610
    crc32.h s10,t0
    sw s10,144(a1)
    RV_COMPLIANCE_HALT
RV_COMPLIANCE_CODE_END

.data
RV_COMPLIANCE_DATA_BEGIN
test_results:
.fill 37,4,-1
RV_COMPLIANCE_DATA_END
