// See LICENSE for license details.

#ifndef SRC_MAIN_C_ACCUMULATOR_H
#define SRC_MAIN_C_ACCUMULATOR_H

#include "rocc-software/src/xcustom.h"


 unsigned long hw_method1_start, 
                     hw_method1_end;


 unsigned long total_cycle_hw_method;






#define k_DO_WRITE 0
#define k_DO_READ 1
#define k_DO_LOAD 2
#define k_DO_ACCUM 3
#define k_DO_BCD 4
#define k_DO_CONVERT 6
#define k_DO_ACCMUL 11

#define XCUSTOM_ACC 0

#define doWrite(y, rocc_rd, data)                                       \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_WRITE);
#define doRead(y, rocc_rd)                                              \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, 0, rocc_rd, k_DO_READ);
#define doLoad(y, rocc_rd, mem_addr)                                    \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, mem_addr, rocc_rd, k_DO_LOAD);
#define doAccum(y, rocc_rd, data) \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_ACCUM);
#define doBCD(y, rocc_rd, data) \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_BCD);
#define doConvert(y, rocc_rd, data) \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_CONVERT);
#define doAccummul(y, rocc_rd, data) \
  ROCC_INSTRUCTION(XCUSTOM_ACC, y, data, rocc_rd, k_DO_ACCMUL);
#

#endif  // SRC_MAIN_C_ACCUMULATOR_H
