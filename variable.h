#pragma once
#ifndef VARIABLE_H
#define VARIABLE_H

typedef signed char     byte;
typedef unsigned char   ubyte;
typedef signed short    halfword;
typedef unsigned short  uhalfword;
typedef signed int      word;
typedef unsigned int    uword;

//�����ڴ�ռ䣬mem����ʼ��ַ��mem_size���ڴ�ռ��С
char *mem;
int mem_size;

//����Ĵ����ļ���reg����ʼ��ַ��reg_size�ǼĴ����ļ��Ĵ�С
int *reg;
int reg_size;

//���������
long PC;

//�����ֶ�(��)
int OPCODE;
int RD;
int FUNCT3;
int RS1;
int RS2;
int FUNCT7;
int CSR;

//�������ֶΣ��ֱ���I��S��SB��U��UJ����������
int I_IMM;
uword I_UIMM;
int S_IMM;
uword S_UIMM;
int SB_IMM;
uword SB_UIMM;
//int U_IMM;
uword U_IMM;    //���ｫU�����������޷���������
int UJ_IMM;
uword UJ_UIMM;

#endif
