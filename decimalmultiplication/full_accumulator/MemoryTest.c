// See LICENSE for license details.

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "include/accumulator.h"
#include "include/translator.h"


//MACRO for selecting BCD digit
#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))


//RDCYCLE is a RISC-V isntruction for cycle count
unsigned long read_cycles(void)
	{
		unsigned long cycles;
		asm volatile ("rdcycle %0" : "=r" (cycles));
		return cycles;

	}



int main() {

  uint64_t data [] = {0xdead, 0xbeef, 0x0bad, 0xf00d}, y;
  uint16_t addr = 1;
  unsigned long cyclestart_read,
		cycleend_read,
		cyclestart_write,
		cycleend_write,
		cyclestart_bcd, 
		cycleend_bcd,
		method1_start,
		method1_end,
		method2_start,
		method2_end,
		method3_start,
		method3_end,
		method4_start,
		method4_end;
    // declare for clock testa

      uint64_t MM [8];
       MM[0] = 0b0000000000000000000000000000000000000000000000000000000000000000;
       MM[1] = 0b0001000100010001000100010001000100010001000100010001000100010001;
       MM[2] = 0b0010001000100010001000100010001000100010001000100010001000100010;
       MM[3] = 0b0011001100110011001100110011001100110011001100110011001100110011;
       MM[4] = 0b0100010001000100010001000100010001000100010001000100010001000100;
       MM[5] = 0b0101010101010101010101010101010101010101010101010101010101010101;
       MM[6] = 0b0110011001100110011001100110011001100110011001100110011001100110;
       MM[7] = 0b0111011101110111011101110111011101110111011101110111011101110111;
       MM[8] = 0b1000100010001000100010001000100010001000100010001000100010001000;
       MM[9] = 0b1001100110011001100110011001100110011001100110011001100110011001;



	 doLoad  (y,1, MM);

  
  //verify Accelerator operation write
  printf("[INFO] Write R[%d] = 0x%lx\n", addr, data[0]);
  cyclestart_write = read_cycles();
  doWrite(y, addr, data[0]);
  cycleend_write = read_cycles();
  printf("Took %lu cycles s to write\n", cycleend_write - cyclestart_write);

  //verify Accelerator operation read
  printf("[INFO] Read R[%d]\n", addr);
  cyclestart_read = read_cycles();
  doRead(y, addr);
  cycleend_read = read_cycles();
  printf("Took %lu cycles s to read\n", cycleend_read - cyclestart_read);

  
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[0]);
 // assert(y == data[0]);

  uint64_t data_accum = -data[0] + data[1];
  printf("[INFO] Accum R[%d] with 0x%lx\n", addr, data_accum);
  doAccum(y, addr, data_accum);
 // assert(y == data[0]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[1]);
 // assert(y == data[1]);

  uint64_t data_addr;
  doTranslate(data_addr, &data[2]);
  printf("[INFO] Load 0x%lx (virt: 0x%p, phys: 0x%p) via L1 virtual address\n",
         data[2], &data[2], (void *) data_addr);
  doLoad(y, addr, &data[2]);
 // assert(y == data[1]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[2]);
 // assert(y == data[2]);

  //----------------------BCD------------------

  
 

 
 
  return 0;
}
