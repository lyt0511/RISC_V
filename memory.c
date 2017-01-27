#include <stdio.h>
#include <stdlib.h>
#include "variable.h"

//�ڴ�Ķ�д����

//���ֽڽ��ж�д����ʱ����Ϊ�ڴ�ĵ�λ����һ���ֽڣ����Բ��漰��С�˴洢������
ubyte read_mem_ubyte(uword addr)
{
	return *((ubyte *)(mem + (addr)));
}

void write_mem_ubyte(uword addr, ubyte val)
{
	*((ubyte *)(mem + (addr))) = val;
}

byte read_mem_byte(uword addr)
{
	return *((byte *)(mem + (addr)));
}

void write_mem_byte(uword addr, byte val)
{
	*((byte *)(mem + (addr))) = val;
}

/*
����16λ���ݵĶ�д��������������Ҫ˵����
1. ����risc-vʹ�õ���С�˴洢����������16λΪ������е�С�˴洢
x86�Ļ���Ҳ��С�˴洢�������ڴ�Ķ�д����8λΪ��������������Ҫ
��ָ��Ĵ洢����һ�ν��洦����������롣
2. �Ƿ�Ϊ������ֻ��res�йأ����res��uhalfword���������޷�������
����halfword������ֻ���з�������
*/

uhalfword read_mem_uhalfword(uword addr)
{
	ubyte *p = (uhalfword *)(mem + addr);
	uhalfword res = 0;
	res = (*(p + 1) + (*(p) << 8));			//ָ���ȡ�Ľ��洦��
	return res;
}

void write_mem_uhalfword(uword addr, uhalfword val)
{
	ubyte *p = (uhalfword *)(mem + addr);
	ubyte val1 = val;
	ubyte val2 = val >> 8;
	*(p) = val2;							//ָ��洢�Ľ��洦��
	*(p + 1) = val1;
}

halfword read_mem_halfword(uword addr)
{
	ubyte *p = (uhalfword *)(mem + addr);
	halfword res = 0;
	res = (*(p + 1) + (*(p) << 8));
	return res;
}

void write_mem_halfword(uword addr, halfword val)
{
	ubyte *p = (uhalfword *)(mem + addr);
	ubyte val1 = val;
	ubyte val2 = val >> 8;
	*(p) = val2;
	*(p + 1) = val1;
}

/*
����32λ���ݵĶ�д��������������Ҫ˵����
1. ����risc-vʹ�õ���С�˴洢����������16λΪ������е�С�˴洢
x86�Ļ���Ҳ��С�˴洢�������ڴ�Ķ�д����8λΪ��������������Ҫ
��ָ��Ĵ洢�������ν��洦����������롣
2. �Ƿ�Ϊ������ֻ��res�йأ����res��uword���������޷�������
����word������ֻ���з�������
*/

//�����ﷸ�˸�������debug��һ�졣��
//֮ǰ����pָ���ʱ��ʹ�õ���uword���ͣ������ܳ����ʱ���ֶ�ȡ��һ��ָ���ʱ�����ǲ���
//���ǽ��и��ֵ������ԣ�֪�����ŷ��������pָ�����͵�����
//���������uword���ͣ���ָ��ָ�������ռ32λ����ôp+1��ʵ����һ��32λ����
//Ȼ�����洦���Ƿֱ�8λ���ݽ��н�����������������ʹ����uword������ô�ͽ�8λ���ݴ浽���ڵļ���32λ�ռ�����
//��ô��Ȼ�Ǵ����
//��ʾ���Ǳ�̵�ʱ��һ��ҪС�ġ�������
uword read_mem_uword(uword addr)
{
	ubyte *p = (ubyte *)(mem + addr);
	uword res = 0;
	res = ((*(p + 2) << 24) + (*(p + 3) << 16) + (*(p) << 8) + *(p + 1));		//ָ���ȡ�Ľ��洦��
	return res;
}

void write_mem_uword(uword addr, uword val)
{
	ubyte *p = (ubyte *)(mem + addr);
	ubyte val1 = val;
	ubyte val2 = val >> 8;
	ubyte val3 = val >> 16;
	ubyte val4 = val >> 24;
	*(p) = val2;							//ָ��洢�Ľ��洦��
	*(p + 1) = val1;
	*(p + 2) = val4;
	*(p + 3) = val3;
}

word read_mem_word(uword addr)
{
	ubyte *p = (ubyte *)(mem + addr);
	word res = 0;
	res = ((*(p + 2) << 24) + (*(p + 3) << 16) + (*(p) << 8) + *(p + 1));
	return res;
}

void write_mem_word(uword addr, word val)
{
	ubyte *p = (ubyte *)(mem + addr);
	ubyte val1 = val;
	ubyte val2 = val >> 8;
	ubyte val3 = val >> 16;
	ubyte val4 = val >> 24;
	*(p) = val2;
	*(p + 1) = val1;
	*(p + 2) = val4;
	*(p + 3) = val3;
}

float read_mem_float(uword addr)
{
	return *((float *)(mem + (addr)));
}

void write_mem_float(uword addr, float val)
{
	*((float *)(mem + (addr))) = val;
}

double read_mem_double(uword addr)
{
	return *((double *)(mem + (addr)));
}

void write_mem_double(uword addr, double val)
{
	*((double *)(mem + (addr))) = val;
}