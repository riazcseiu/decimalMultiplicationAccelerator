/* ------------------------------------------------------------------ */
/* Decimal Number Multiplication Testing tools                       */
/* ------------------------------------------------------------------ */
/* Riaz ul haque Mian , DSL, NAIST   git version */
/* ----------------------------------------------------------------+- */
/*                                                 right margin -->|  */

// DecMulTimeMeasure.c -- first read string form text file as input
//  convert the string to decFloat 64 bit format decDobule,
// Multiply the Number together, and write  the result to another
// text file outplut.txt. 
//#define _CRT_SECURE_NO_DEPRECATE
#define  DECNUMDIGITS 34           // work with up to 34 digits
#include"decDouble.h"
#include <stdio.h>                 // for printf
#include <time.h>
#include <string.h>
#include "rocc_charcunt.h"


unsigned long read_cycles(void)
	{
	     unsigned long cycles;
	     asm volatile ("rdcycle %0" : "=r" (cycles));
             return cycles;
	}	

	/*
	unsigned long data = 0b01011111;
static inline void accum_load(int idx, void *ptr)
  	{
   	printf("Load\n");
   	asm volatile ("fence");
   	ROCC_INSTRUCTION_SS(0, (uintptr_t) ptr, idx, 2);
	}*/

static inline unsigned long accum_BCDadd( unsigned long data, unsigned long data1)
	{       
	printf("MUL_DEC");
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
	printf("MUL_DEC");
	unsigned long result;
	asm volatile ("fence");
   	ROCC_INSTRUCTION_DSS(0,result, data1, data, 7);
	return result;
	}



static inline unsigned long accum_DPD_BCD( unsigned long data, unsigned long data1)
	{       
	printf("DPDBCD_r");
	unsigned long result;
	asm volatile ("fence");
   	ROCC_INSTRUCTION_DSS(0,result, data1, data, 8); //bpd-bdc (doBCD) is assign as function 6
	return result;

	}

static inline unsigned long accum_BCD_DPD( unsigned long data, unsigned long data1)
	{       
	printf("BCD_DPD_r");
	unsigned long result;
	asm volatile ("fence");
   	ROCC_INSTRUCTION_DSS(0,result, data1, data, 9); //BCD-DPD (doDPD) is assign as function 8
	return result;
	}

int main() 
{
	decDouble a, b , c,d, temp1,temp2;// working numbers 64 bit format
	decContext set;                  // working context
	char string1[DECDOUBLE_String]; // 25 for 64 bit String1 is type of numeric string
	decContextDefault(&set, DEC_INIT_DECDOUBLE); // initialize as 64 bit operation

	//setep 1
	//--------------- reading form text file

	/*riazs	FILE *ptr_file_read, *ptr_file_readB,*ptr_file_write , *Mptr_file_write;
	char buf[26]; //	/////////////////////////////////////////////////////////////////////
	unsigned long BCD_val =  0b000100100010001100010011001001110011000000100000000100010000; //122313273020110 
	unsigned long DPD_val =  0b001010010011001011010111011000010000001001000; //122313273020110 


	char bufB[26];
	char multiplicand[9000][26];
	char multiplaier[9000][26];
	//int num;
	
	//-------------replace file name here -------------------

	char fileNameA [40] = "final_result_b.txt";
	char fileNameB [40] = "final_result_b.txt";
	
        //-----------------------------------------------------   


        ptr_file_read = fopen(fileNameA, "r"); //Name of the input file
	
	if (!ptr_file_read)
		{ 
		printf("problem reading inputA.txt");
	    	return 1;
		}
	ptr_file_readB = fopen(fileNameB, "r"); //Name of the input file
	if (!ptr_file_read)
		{	
		printf("problem reading inputB.txt");
		return 1;
		}

	ptr_file_write = fopen("output.txt", "a+");

	if (!ptr_file_write)
		{
		printf("problem Writing Output.txt");
		return 1;
		}

	Mptr_file_write = fopen("Moutput.txt", "a+");

	if (!ptr_file_write)
		{
		printf("problem Writing MOutput.txt");
		return 1;
		}
	//while (fgets(buf, 100, ptr_file_read) != NULL) //read untill new line

	for (int i = 0; fgets(buf, 100, ptr_file_read) != NULL; i++) //read untill new line
		{
	    	// buf[strcspn(buf, "\n")] = 0; //remove \n from string
	     	buf[strcspn(buf, "\r\n")] = 0; 
		strcpy(multiplicand[i], buf); // assign multiplicand max 100
		}
	fclose(ptr_file_read); // complete all  cover all string
	//now multiplicand[] has all the multiplicand which 
	 //------- end reading form tex file 
	for (int i = 0; fgets(bufB, 100, ptr_file_readB) != NULL; i++) //read untill new line
		{
		//	bufB[strcspn(bufB, "\n")] = 0; //remove \n from string
		bufB[strcspn(bufB, "\r\n")] = 0; 
		strcpy(multiplaier[i], bufB); // assign multiplicand max 100
		}
	fclose(ptr_file_readB); // complete all  cover all string
	//step 2 calculation in both method
	//-----------rocc test------------
	riaze*/		
		
	 
       

	unsigned long cyclestart,cycleend, modcyclestart,modcycleend,rocccyclestart,rocccycleend,BCD_cyclestart,BCD_cycleend ,aaa,bbb,aaa1,bbb1,aaa2,bbb2; // declare for clock test
	rocccyclestart = read_cycles();
	//accum_load(0, &data);
	//	printf("data is %ld\n",data);
        rocccycleend = read_cycles();
	// printf("Took in Method2 Combination  %lu cycles\n", rocccycleend - rocccyclestart);
        // unsigned long X = 0b011000001101101101101101101101101101100000001110111011101110000;
      	//  unsigned long Y =0b011000001101101101101101101101101101100000001110111011101110000;


	/////////////////////////////////////////////////////////////////////
	unsigned long BCD_val =  0b000100100010001100010011001001110011000000100000000100010000; //122313273020110(h) 
	unsigned long DPD_val =  0b001010010011001011010111011000010000001001000; //5265AEC2048(H)

	unsigned long X =0b10011001100110000110011101111001;// 0b1000000100010011001101110111100010000011010001000000000000001000;
	//0b011000001101101101101101101101101101100000001110111011101110000;
	unsigned long Y = 0b1001100110011000011001110111100;// 10b1000000100010011001101110111100010000011010001000000000000001000;
	//0b011000001101101101101101101101101101100000001110111011101110000;
	
	for (int mohon =0 ; mohon <10; mohon++)
		{
		aaa = read_cycles();
		//unsigned long BCDresult = accum_BCDadd(X, Y);
		//result = accum_read(0);
        	// unsigned long BCDresult = accum_BCDconvert(X, Y);
 		unsigned long BCDresult = accum_DPD_BCD(DPD_val, Y);
		bbb = read_cycles();
		printf("Took %lu cycles to Conversion  %lu result \n", bbb - aaa, BCDresult);
		X=X+10; Y=Y+10;
		printf("resutl should 97 %d, %ld\n" ,mohon,BCDresult);
		}


	for (int mohon1 =0 ; mohon1 <10; mohon1++)
		{
		aaa1 = read_cycles();
		//unsigned long BCDresult = accum_BCDadd(X, Y);
		//result = accum_read(0);
        	// unsigned long BCDresult1 = accum_BCDadd(X, Y);
         	unsigned long BCDresult1 = accum_BCD_DPD(BCD_val, Y);
		bbb1 = read_cycles();
		printf("Took %lu cycles to convert DPD  %lu result \n", bbb1 - aaa1, BCDresult1);
		X=X+10; Y=Y+10;
		printf("resutl should  %d, %ld\n" ,mohon1,BCDresult1);
		}
	

	for (int mohon2 =0 ; mohon2 <10; mohon2++)
		{
		aaa2 = read_cycles();
		unsigned long BCDresult2 = accum_BCDmul(X, Y);
		//result = accum_read(0);
		bbb2 = read_cycles();
		printf("Took %lu cycles to Full mull  %lu result \n", bbb2 - aaa2, BCDresult2);
		X=X+10; Y=Y+10;
		printf("resutl should 97 %d, %ld\n" ,mohon2,BCDresult2);
		}












	//accum_load(0, &data);
	BCD_cyclestart = read_cycles();

	//unsigned long BCDresult = accum_BCDadd(X, Y);
	//result = accum_read(0);

         BCD_cycleend = read_cycles();
 	// printf("Took %lu cycles to BCD add %lu result \n", BCD_cycleend - BCD_cyclestart, BCDresult);
	//-------------------------------	
			
			
	clock_t begin_decimal = 0; //initialize time
	clock_t end_decimal = 0;
        int c1 = 0;
      


	char multiplicand[9000][26];
	char multiplaier[9000][26];
	



 	strncpy (multiplicand[0],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplicand[1],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplicand[2],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplicand[3],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplicand[4],"+1E-360", strlen("+1E-360")+1);

 	strncpy (multiplaier[0],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplaier[1],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplaier[2],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplaier[3],"+1E-360", strlen("+1E-360")+1);
 	strncpy (multiplaier[4],"+1E-360", strlen("+1E-360")+1);

	for (c1 = 0 ; c1<2;c1++) //input loop changing input
		{
	    
			//int i = 0;
			decDoubleFromString(&a, multiplicand[c1], &set);
			decDoubleFromString(&b, multiplaier[c1], &set);
			temp1 = a; temp2 = b; 
			begin_decimal = clock();
			for(int m=0;m<5;m++) //doing the same operation repet
				{	 
					a = temp1; b = temp2;
                                 	cyclestart = read_cycles();
					decDoubleMultiply(&a, &a, &b, &set);    // a=aXb
					cycleend = read_cycles();
					printf("Took %lu cycles(SW)\n", cycleend - cyclestart);
					//decDoubleAdd(&a, &a, &b , &set);
				
				}	
		    	end_decimal = clock();
			//r	fprintf(ptr_file_write, "%lf \n", (double)( end_decimal- begin_decimal) / CLOCKS_PER_SEC);
			decDoubleToString(&a, string1);
            		printf("Exsisting function \n");
	    		//  printf("test\n");	    
	    		// printf(" %s\n",  string1);
	    		// printf(" %s\n",  multiplicand[c1]);
	    		// printf(" %s\n",  multiplicand[c1+1]);
	    		printf("%s x %s => %s\n", multiplicand[c1], multiplaier[c1], string1);
		}
	
  
 	// printf ("time modify: % lf \n",(double)(end_decimal-begin_decimal)/CLOCKS_PER_SEC);
	//solution with exsisting function
  	clock_t begin_modify=0;
  	clock_t end_modify = 0;
	int c2 = 0;

  	for (c2 = 0 ; c2<3;c2++)
		{
	    		// int i = 0;
	  		decDoubleFromString(&c, multiplicand[c2], &set);
	  		decDoubleFromString(&d, multiplicand[c2 + 1], &set);
	  		temp1 = c; temp2 = d;
	  		begin_modify = clock();
	  		for (int m = 0; m<5; m++) //doing the same operation repet
	  			{
		  			c = temp1; d = temp2;
                 			modcyclestart = read_cycles();
					MdecDoubleMultiply(&c, &c, &d, &set);    // a=aXb
					modcycleend = read_cycles();
					printf("Took %lu cycles (COMB) \n", modcycleend - modcyclestart);
				}
	  		end_modify = clock();
	  		//r fprintf(Mptr_file_write, "%lf \n", (double)(end_modify- begin_modify) / CLOCKS_PER_SEC);
	  		decDoubleToString(&c, string1);
	  		printf("Modify function \n");
	  		printf("%s x %s => %s\n", multiplicand[c2], multiplicand[c2 + 1], string1);
		}
	
 	//clock_t end=clock();
 	// printf ("time exsisting %lf \n",(double)(end-begin)/CLOCKS_PER_SEC);
	//step 3  // ------------ writing result in text file
	// fprintf(ptr_file_write,"%lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
    	//r	fclose(ptr_file_write);
	getchar();
  	return 0;
 
  } // main 

