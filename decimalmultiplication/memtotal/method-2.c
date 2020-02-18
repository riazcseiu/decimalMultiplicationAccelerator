#include <stdio.h>
#include <stdint.h>
#include "rocc_memtotal.h"
//#include "rocc_charcunt.h"
#include "rocc.h"


/*
#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))



static inline unsigned long accum_BCDadd( unsigned long data, unsigned long data1)
{       
	printf("DEC_ADD_M1");
	unsigned long result;
	asm volatile ("fence");
   	ROCC_INSTRUCTION_DSS(0,result, data1, data, 4);
	return result;

}

*/









uint64_t mem_array[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 12,13,14,15};

int main()
{
  uint64_t mem_total_hw = 10;
  uint64_t mem_total_sw = 0;
  memtotal (mem_total_hw, mem_array, 10);
  for (int i = 0; i < 10; i++) {
    mem_total_sw += mem_array[i];
  }
  printf ("mem_total_hw = %d\n", mem_total_hw);
  printf ("mem_total_sw = %d\n", mem_total_sw);

  //uplpding multiplicand multiple

unsigned long result;


 //A sample value of multiplicand in BCD
 uint64_t X_64 = 0b0000000100010011001101110111100010000011010001000000000000001000;
 //A sample value of multiplier in BCD
 uint64_t Y_64 =0b001000100010011001101110111100010000011010001000000000000001000;
 //Adding two BCD number
 // uint64_t bcdadd= accum_BCDadd(X_64,Y_64);


  

 //generating multiplicand multiple
unsigned long long MM[10];
		MM[0]= 0b000000000000000000000000000000000000000000000000000000000000000;
		MM[1]= X_64;


MM[3]= X_64;
 MM[4]= X_64;
 MM[5]= X_64;MM[6]= X_64;MM[7]= X_64;MM[8]= X_64;MM[9]= X_64;
		
		/*

	for (int mulcount = 1; mulcount<9 ; mulcount=mulcount+1)
		MM[mulcount+1] =  accum_BCDadd(MM[1], MM[mulcount]);


	for (int mmp = 0; mmp<10 ; mmp++)
		 printf(" Multiplicand multiple MM[%u] %ld \n",mmp, MM[mmp]);


		*/
	//parallel HW for decimal accululation

	memmul (mem_total_hw, MM, 10);


	


}
