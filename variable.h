#pragma once
#ifndef VARIABLE_H
#define VARIABLE_H

typedef signed char     byte;
typedef unsigned char   ubyte;
typedef signed short    halfword;
typedef unsigned short  uhalfword;
typedef signed int      word;
typedef unsigned int    uword;

//分配内存空间，mem是起始地址，mem_size是内存空间大小
char *mem;
int mem_size;

//分配寄存器文件，reg是起始地址，reg_size是寄存器文件的大小
int *reg;
int reg_size;

//程序计数器
long PC;

//译码字段(改)
int OPCODE;
int RD;
int FUNCT3;
int RS1;
int RS2;
int FUNCT7;
int CSR;

//立即数字段，分别有I，S，SB，U，UJ五类立即数
int I_IMM;
uword I_UIMM;
int S_IMM;
uword S_UIMM;
int SB_IMM;
uword SB_UIMM;
//int U_IMM;
uword U_IMM;    //这里将U立即数当做无符号数处理
int UJ_IMM;
uword UJ_UIMM;

#endif
