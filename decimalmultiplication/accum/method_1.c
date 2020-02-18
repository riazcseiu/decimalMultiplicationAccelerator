//NAIST Dependable System Lab
#include "rocc_charcunt.h"
#include<stdio.h>



#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))



unsigned long read_cycles(void)
 {
   unsigned long cycles;
   asm volatile ("rdcycle %0" : "=r" (cycles));
   return cycles;

}



static inline void accum_write(int idx, unsigned long data)
{
	
	printf("Write\n");
	ROCC_INSTRUCTION_SS(0, data, idx, 0);
}


static inline unsigned long accum_read(int idx)
{
	printf("READ\n");
	unsigned long value;
	ROCC_INSTRUCTION_DSS(0, value, 0, idx, 1);
	return value;
}

static inline void accum_load(int idx, void *ptr)
{
	printf("LOAD\n");
	asm volatile ("fence");
	ROCC_INSTRUCTION_SS(0, (uintptr_t) ptr, idx, 2);
}

static inline void accum_add(int idx, unsigned long addend)
{      
	printf("BINARY_ADD\n");
	ROCC_INSTRUCTION_SS(0, addend, idx, 3);
}



static inline unsigned long accum_BCDadd( unsigned long data, unsigned long data1)
{       
	printf("DEC_ADD_M1");
	unsigned long result;
	asm volatile ("fence");
   	ROCC_INSTRUCTION_DSS(0,result, data1, data, 4);
	return result;

}




static inline unsigned long accum_BCDconvert( unsigned long data, unsigned long data1)
{       
	printf("CONVERT_r");
	unsigned long result;
	asm volatile ("fence");
   	ROCC_INSTRUCTION_DSS(0,result, data1, data, 6); //convert is assign as function 6
	return result;

}

	
static inline unsigned long accum_BCDmul( unsigned long data, unsigned long data1)
{       
	printf("MULTIPLICATION_r");
	unsigned long result;
	asm volatile ("fence");
   	ROCC_INSTRUCTION_DSS(0,result, data1, data, 7); //multiplication is assign as function 7
	return result;

}







//unsigned long data = 0x3421L;
unsigned long data = 0b10011001100110000110011101111001;// 10b1000_0001_0001_0011_0011_0111_0111_1000_1000_0011_0100_0100_0000_0000_0000_1000;
//0b011000001101101101101101101101101101100000001110111011101110000;
unsigned long data1 =0b10011001100110000110011101111001; // 0b1000000100010011001101110111100010000011010001000000000000001000;
//0b011000001101101101101101101101101101100000001110111011101110000;



typedef struct
{
unsigned  D1  :4,
 D2  :4,
 D3  :4,
 D4  :4,
 D5  :4,
 D6  :4,
 D7  :4,
 D8  :4,
 D9  :4,
 D10 :4,
 D11 :4,
 D12 :4,
 D13 :4,
 D14 :4,
 D15 :4,
 D16 :4;

}hi_r ;


int main(void)
{
	unsigned long result;
	unsigned long LOAD_cyclestart, LOAD_cycleend,  ADD_cyclestart, ADD_cycleend , BCD_cyclestart, BCD_cycleend,aaa,aaa1,bbb,bbb1,aaa4,bbb4,method1_start,method1_end;// declare for clock test
        
       	LOAD_cyclestart = read_cycles();

									

       //load and add
	accum_load(0, &data);
	printf("data is %ld\n",data);
       
        
	//if (result != data + 2)
         LOAD_cycleend = read_cycles();
  printf("Took %lu cycles to loadd \n", LOAD_cycleend - LOAD_cyclestart);


       	ADD_cyclestart = read_cycles();

	accum_add(0, 2);
	result = accum_read(0);
	printf("data+2=%ld\n",result);
//	if (result != data + 2)
	//	return 1;
       // write and add
         ADD_cycleend = read_cycles();
         printf("Took %lu cycles to add \n", ADD_cycleend - ADD_cyclestart);



	accum_write(0, 3);
	printf("writeAccumulator 3\n");

	accum_add(0, 1);
	printf("Add  N ccumulator 1\n");
	result = accum_read(0);

//	if (result != 4)
//		return 2;
        printf("resutl%ld\n",result);  
       //bcd operation start
       //====================================


         
//////////////////////////////////////////////////////////////////////
unsigned long X_32 = 0b10011001100110000110011101111001;
unsigned long Y_32 = 0b10011001100110000110011101111001;


//////////////////////////////////////////////////////////////////////
uint64_t X_64 = 0b0000000100010011001101110111100010000011010001000000000000001000;
//0b011000001101101101101101101101101101100000001110111011101110000;
uint64_t Y_64 =0b001000100010011001101110111100010000011010001000000000000001000;
//0b011000001101101101101101101101101101100000001110111011101110000;
hi_r mul = *(hi_r *)&X_64;
printf("   %2hhu - %2hhu  value : %u (deg. F)\n", 60, 63, mul.D16);




for (int mega =0; mega <19; mega++)
{
printf("single cycle test start\n");
unsigned long bcdadd,bcdconv,bcdmul;
bcdadd= accum_BCDadd(X_64,Y_64);
bcdconv=accum_BCDconvert(X_32, Y_32);
bcdmul= accum_BCDmul(X_64, Y_64);
printf("add=%ld, conv=%ld, mul=%ld \n where Xconv= %ld Y_64=%ld X_64=%ld ",bcdadd,bcdconv,bcdmul,X_32,Y_64,X_64);
printf("single cycle end");
}

     


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
		MM[mulcount+1] =  accum_BCDadd(MM[1], MM[mulcount]);


	for (int mmp = 0; mmp<10 ; mmp++)
		 printf(" Multiplicand multiple MM[%u] %ld \n",mmp, MM[mmp]);

printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);



for (int ii=0; ii <64 ; ii=ii+4)
{
	printf("initial porduct is  and the digit is%x \n", MID(Y_64,ii,ii+4));

}
printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);

		
__uint128_t product=0;

for (int ii=0; ii <64 ; ii=ii+4)
{
	//printf("initial porduct is %lu and the digit is%x \n",product, MID(Y_64,ii,ii+4));
	product = accum_BCDadd(product , MM[ MID(Y_64,ii,ii+4)]);
	printf ("steps=%d,product=%llu ,digit of Y=%x X= %lu  Y= %lu \n",ii,product,  MID(Y_64,ii,ii+4), X_64,Y_64);
        product << 4;
}
 
  	method1_end = read_cycles();

  printf("Took %lu cycles to X=%ld, Y=%ld, Method-1  %lu \n",method1_end - method1_start ,X_64,Y_64);

  }

// printf(" Multiplicand multiple d, mm , result, x %d , %ld, %ld \n", mm , MM[mm+1],X_64);

printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);



for (int ii=0; ii <64 ; ii=ii+4)
{
	printf("initial porduct is  and the digit is%x \n", MID(Y_64,ii,ii+4));

}


printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);






for (int mohon =0 ; mohon <2; mohon++)
{
	
	aaa = read_cycles();

       //  unsigned long BCDresult = accum_BCDadd(X, Y);
//	result = accum_read(0);
        unsigned long BCDresult = accum_BCDconvert(X_32, Y_32);


         bbb = read_cycles();

  printf("Took %lu cycles to Conversion  %lu is result for input %lu  \n", bbb - aaa, BCDresult,X_32);

X_32=X_32+0; Y_32=Y_32+0;
	
	//printf("resutl %d, %ld\n" ,mohon,BCDresult);
}

printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);



for (int shiuly =0 ; shiuly <2; shiuly++)
{
	
	aaa4 = read_cycles();

         unsigned long BCDresult = accum_BCDadd(X_64, Y_64);
//	result = accum_read(0);
        // unsigned long BCDresult1 = accum_BCDadd(X, Y);


         bbb4 = read_cycles();

  printf("Took %lu cycles to X=%ld, Y=%ld, Multiplication  %lu \n", bbb4 - aaa4,X_64,Y_64, BCDresult);

X_64=X_64+0; Y_64=Y_64+0;
	
//	printf("resutl should 97 RRR %d, %ld\n" ,mohon1,BCDresult1);
}

 
printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);







for (int mohon1 =0 ; mohon1 <2; mohon1++)
{
	
	aaa1 = read_cycles();

         unsigned long BCDresult = accum_BCDmul(X_64, Y_64);
//	result = accum_read(0);
        // unsigned long BCDresult1 = accum_BCDadd(X, Y);


         bbb1 = read_cycles();

  printf("Took %lu cycles to X=%ld, Y=%ld, Multiplication  %lu \n", bbb1 - aaa1,X_64,Y_64, BCDresult);

X_64=X_64+0; Y_64=Y_64+0;
	
//	printf("resutl  %d, %ld\n" ,BCDresult1);
}

  //----------------------BCD------------------

  
 
//unsigned long X =0b1001100110011001100110011001100110011001100110011001100110011001;// 0b0011000001001001001101001000001100001000000001100101011101110000;
// 0b0011100110000011100001000100001110000100100010010001000100010111;// 0b0011000001001001001101001000001100001000000001100101011101110000;
//                          // 3_9_8_3_8_4_4_3_8_4_8_9_1_1_1_7_ //3_0_4_9_3_4_8_3_0_8_0_6_5_7_7_0
//unsigned long Y = 0b1001100110011001100110011001100110011001100110011001100110011001;//0b0011000001001001001101001000001100001000000001100101011101110000;
//                                  // 0b0011100110000011100001000100001110000100100010010001000100010111;//0b0011000001001001001101001000001100001000000001100101011101110000;
//


//-------------------------------BCD END -------------
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
printf(" Xconv= %ld X_64=%ld Y_64=%ld ",X_32,Y_64,X_64);



      	 return 0;
}

