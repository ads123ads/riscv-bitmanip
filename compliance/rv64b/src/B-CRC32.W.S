#include "compliance_test.h"
#include "compliance_io.h"
#include "test_macros.h"

RV_COMPLIANCE_RV32M

RV_COMPLIANCE_CODE_BEGIN
    la a1,test_results
    li s3, 0xeadf76b9d77b6ecd
    crc32.w s10,s3
    sd s10,0(a1)
    li s2, 0x991e56a136a9a6d7
    crc32.w t4,s2
    sd t4,8(a1)
    li s9, 0x75be118b219954ae
    crc32.w s0,s9
    sd s0,16(a1)
    li s3, 0x201eccb891f3a75b
    crc32.w t4,s3
    sd t4,24(a1)
    li t1, 0x5259a8e16723f89c
    crc32.w a0,t1
    sd a0,32(a1)
    li a0, 0x80b445926042e65d
    crc32.w a4,a0
    sd a4,40(a1)
    RV_COMPLIANCE_HALT
RV_COMPLIANCE_CODE_END

.data
RV_COMPLIANCE_DATA_BEGIN
test_results:
.fill 6,8,-1
RV_COMPLIANCE_DATA_END
