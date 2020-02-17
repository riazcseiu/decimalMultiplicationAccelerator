// See LICENSE for license details.

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "include/accumulator.h"
#include "include/translator.h"



#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))


//------------------------------
unsigned long read_cycles(void)

{

unsigned long cycles;

asm volatile ("rdcycle %0" : "=r" (cycles));
return cycles;

}
//---------------------------------



int main() {

  uint64_t data [] = {0xdead, 0xbeef, 0x0bad, 0xf00d}, y;
  uint16_t addr = 1;
  unsigned long cyclestart_read,cycleend_read,cyclestart_write,cycleend_write,cyclestart_bcd, cycleend_bcd,method1_start,method1_end; // declare for clock testa
  
  printf("[INFO] Write R[%d] = 0x%lx\n", addr, data[0]);
  cyclestart_write = read_cycles();
  doWrite(y, addr, data[0]);
  cycleend_write = read_cycles();
  printf("Took %lu cycles s to write\n", cycleend_write - cyclestart_write);


  printf("[INFO] Read R[%d]\n", addr);
  cyclestart_read = read_cycles();
  doRead(y, addr);
  cycleend_read = read_cycles();
  printf("Took %lu cycles s to read\n", cycleend_read - cyclestart_read);

  
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[0]);
  assert(y == data[0]);

  uint64_t data_accum = -data[0] + data[1];
  printf("[INFO] Accum R[%d] with 0x%lx\n", addr, data_accum);
  doAccum(y, addr, data_accum);
  assert(y == data[0]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[1]);
  assert(y == data[1]);

  uint64_t data_addr;
  doTranslate(data_addr, &data[2]);
  printf("[INFO] Load 0x%lx (virt: 0x%p, phys: 0x%p) via L1 virtual address\n",
         data[2], &data[2], (void *) data_addr);
  doLoad(y, addr, &data[2]);
  assert(y == data[1]);

  printf("[INFO] Read R[%d]\n", addr);
  doRead(y, addr);
  printf("[INFO]   Received 0x%lx (expected 0x%lx)\n", y, data[2]);
  assert(y == data[2]);

 
 
 
  //----------------------BCD------------------

  
 
unsigned long X =0b1001100110011001100110011001100110011001100110011001100110011001;// 0b0011000001001001001101001000001100001000000001100101011101110000;
// 0b0011100110000011100001000100001110000100100010010001000100010111;// 0b0011000001001001001101001000001100001000000001100101011101110000;
//                          // 3_9_8_3_8_4_4_3_8_4_8_9_1_1_1_7_ //3_0_4_9_3_4_8_3_0_8_0_6_5_7_7_0
unsigned long Y = 0b1001100110011001100110011001100110011001100110011001100110011001;//0b0011000001001001001101001000001100001000000001100101011101110000;
//                                  // 0b0011100110000011100001000100001110000100100010010001000100010111;//0b0011000001001001001101001000001100001000000001100101011101110000;
//
for (int serial = 0; serial<9; serial ++)
{	
printf("[INFO] Accum BCD R[%d] with 0x%lx\n", X,Y);
cyclestart_bcd = read_cycles();
doBCD(y,X,Y)
cycleend_bcd = read_cycles();
printf("in %lu  in  %lu  out %lu \n",X,Y,y);
printf("Too New riaz %lu cycle for BCD \n start %ld \n end %ld", cycleend_bcd - cyclestart_bcd,cyclestart_bcd, cycleend_bcd);

X=X+10;
Y=Y+10;
}



//-------------------------------BCD END -------------
 // method 1-------------------------
 //


         
//////////////////////////////////////////////////////////////////////
unsigned long X_32 = 0b10011001100110000110011101111001;
unsigned long Y_32 = 0b10011001100110000110011101111001;


//////////////////////////////////////////////////////////////////////
uint64_t X_64 = 0b0000000100010011001101110111100010000011010001000000000000001000;
//0b011000001101101101101101101101101101100000001110111011101110000;
uint64_t Y_64 =0b001000100010011001101110111100010000011010001000000000000001000;
//0b011000001101101101101101101101101101100000001110111011101110000;
//hi_r mul = *(hi_r *)&X_64;
//printf("   %2hhu - %2hhu  value : %u (deg. F)\n", 60, 63, mul.D16);



    

for (int ii=0; ii <64 ; ii=ii+4)
{
	printf("initial porduct is  and the digit is%x \n", MID(Y_64,ii,ii+4));

}

for (int any = 1; any<20; any++)
{
  	method1_start = read_cycles();


unsigned long long MM[10];
		MM[0]= 0b000000000000000000000000000000000000000000000000000000000000000;
		MM[1]= X_64; 

	for (int mulcount = 1; mulcount<9 ; mulcount=mulcount+1)
      doBCD(MM[mulcount+1],MM[1], MM[mulcount]);

/*
	for (int mmp = 0; mmp<10 ; mmp++)
		 printf(" Multiplicand multiple MM[%u] %ld \n",mmp, MM[mmp]);

printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);



for (int ii=0; ii <64 ; ii=ii+4)
{
	printf("initial porduct is  and the digit is%x \n", MID(Y_64,ii,ii+4));

}
printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);
*/
		
__uint128_t product=0;

for (int ii=0; ii <36 ; ii=ii+4)
{
	//printf("initial porduct is %lu and the digit is%x \n",product, MID(Y_64,ii,ii+4));
	 doBCD(product,product , MM[ MID(Y_64,ii,ii+4)]);
//	printf ("steps=%d,product=%llu ,digit of Y=%x X= %lu  Y= %lu \n",ii,product,  MID(Y_64,ii,ii+4), X_64,Y_64);
        product << 4;
}
 
  	method1_end = read_cycles();

  printf("Took %lu cycles to X=%ld, Y=%ld, Method-1  \n",method1_end - method1_start ,X_64,Y_64);

  }




 // mehtod 1 end 
 
 
 
 
 
  return 0;
}
