*
The project is developed as part of Computer Architecture class
Project Name: Functional/Pipeline Simulator for simpleRISC Processor
Developer's Name:
Developer's Email id:
Date:
*/

/* mySimpleSim.cpp
   Purpose of this file: implementation file for mySimpleSim
*/

#include "mySimpleSim.h"
#include <stdlib.h>
#include <stdio.h>

//Register file/*
The project is developed as part of Computer Architecture class
Project Name: Functional/Pipeline Simulator for simpleRISC Processor
Developer's Name:
Developer's Email id:
Date:
*/

/* mySimpleSim.cpp
   Purpose of this file: implementation file for mySimpleSim
*/

#include "mySimpleSim.h"
#include <stdlib.h>
#include <stdio.h>

//Register file
static unsigned int R[16];
static int PC=-4;
//flags
static int gt,eq;
//memory
static unsigned char MEM[4000];
static int immediate;
//intermediate datapath and control path signals
static unsigned int instruction_word;
static unsigned int operand1;
static unsigned int operand2;
static int branchPC;
static int isBranchTaken;
static int isImm;
static int isAdd;
static int isSub;
static int isMul;
static int isDiv;
static int isMod;
static int isLsl;
static int isLsr;
static int isAsr;
static int isOr;
static int isAnd;
static int isNot;
static int isMov;
static int isSt;
static int isLd;
static int isBeq;
static int isBgt;
static int isRet;
static int isWb;
static int isUBranch;
static int isCall;
static int imm;
static int aluResult;
static int branchTarget;
void run_simplesim() {
  while(1) {
    fetch();
    decode();
    execute();
    mem();
    write_back();
  }
}

// it is used to set the reset values
//reset all registers and memory content to 0
void reset_proc() {

}

//load_program_memory reads the input memory, and pupulates the instruction
// memory
void load_program_memory(char *file_name) {
  FILE *fp;
  unsigned int address, instruction;
  fp = fopen(file_name, "r");
  if(fp == NULL) {
    printf("Error opening input mem file\n");
    exit(1);
  }
  while( fscanf(fp, "%x %x", &address, &instruction) != EOF) {
    write_word(MEM, address, instruction);
  }
  fclose(fp);
}

//writes the data memory in "data_out.mem" file
void write_data_memory() {
  FILE *fp;
  unsigned int i;
  fp = fopen("data_out.mem", "w");
  if(fp == NULL) {
    printf("Error opening dataout.mem file for writing\n");
    return;
  }

  for(i=0; i < 4000; i = i+4){
    fprintf(fp, "%x %x\n", i, read_word(MEM, i));
  }
  fclose(fp);
}

//reads from the instruction memory and updates the instruction register
void fetch()
{
          if(isBranchTaken){
             PC=BranchPc;
                 }
           else{
		PC=PC+4;
               } 

          
	unsigned int *a=read_word(MEM,PC);
	instruction_word=*a;	
	
}
void decode() 
{int e;
if(isRet){

operand1=r[15];

}
else{

e=((instruction_word & 0x003c0000)>>18);

operand1=r[e];
}
if(isSt){

e=((instruction_word & 0x03c00000)>>22);
operand2=r[e];
}
else{

e=((instruction_word & 0x0003c000)>>14);

operand2=r[e];
}
 if(isImm){
 if(((instruction_word & 0x00030000)>>16)==0){
 imm=(instruction_word & 0x0000ffff);
	 
 
 }
 if(((instruction_word & 0x00030000)>>16)==1){
 imm=(instruction_word | 0xffff0000);
	 
 
 }
 if(((instruction_word & 0x00030000)>>16)==2){
 imm=(instruction_word)<<16;
	 
 
 }
 
 }
 if(isBranchTaken){
 
 
 
 }
 
 
 
}
//executes the ALU operation based on ALUop

 
 
 
//perform the memory operation
rand1=r[e];
}
if(isSt){

e=((instruction_word & 0x000001e0)>>5);
operand2=r[e];
}
void execute() 
{
	
	/*1 st Part*/
	if(isRet)
	branchPC=operand1;
	else
        branchPC=branchTarget;

        /*2 nd Part*/
	if(isUBranch||(isBeq&&eq)||(isBgt&&gt))
	isBranchTaken=1;
	else 
	isBranchTaken=0;

	/*ALU PART */
	int A,B;	
	if(isImm==1)
	B=imm;
	else
	B=operand2;
	A=operand1;
	if(isMul)
	{
	aluResult=A*B;
	return;
	}
	else if(isDiv)
	{
	aluResult=A/B;
	return;
	}
	else if(isMod)
	{
	aluResult=A%B;
	return;
	}
	else if(isOr)
	{
	aluResult=A|B;
	return;
	}
	
	else if(isNot)
	{
	aluResult=A|B; /*HAVE TO DO*/
	return;
	}
	
	else if(isMov) /*HAVE TO DO*/
	{
	aluResult=A|B;
	return;
	}
	
	else if(isAnd)
	{
	aluResult=A&B;
	return;
	}

	else if(isAdd)
	{
	aluResult=A+B;
	return;
	}

	else if(isSub)
	{
	aluResult=A-B;
	return;
	}

	else if(isCmp)
	{
	if(A>B)
	{
	   eq=0;
	   gt=1;	
	}
	else if(A==B)
	{
	   eq=1;
	   gt=0;
	}
	return;
	}
	
	else if(isLd)  /*HAVE TO DO*/
	{
	aluResult=A|B;
	return;
	}
	
	else if(isSt)
	{
	aluResult=A|B;
	return;
	}
	
	else if(isLsl)
	{
	aluResult=A<<B;
	return;
	}
	
	else if(isLsr)
	{
	aluResult=A>>B;
	return;
	}
	
	else if(isAsr)
	{
	unsigned int a=A|0x80000000;
	unsigned int b=A<<1;
	b=b>>B;
	b=b|a;
	aluResult=A|B;
	return;
	}
	   
	
}

void mem() {
}
//writes the results back to register file
void write_back() {
}

int * read_word(char *mem, unsigned int address) {
  int *data;
  data =  (int*) (mem + address);
  return *data;
}

void write_word(char *mem, unsigned int address, unsigned int data) {
  int *data_p;
  data_p = (int*) (mem + address);
  *data_p = data;
}
