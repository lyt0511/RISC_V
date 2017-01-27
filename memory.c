#include <stdio.h>
#include <stdlib.h>
#include "variable.h"

//内存的读写函数

//对字节进行读写操作时，因为内存的单位就是一个字节，所以不涉及大小端存储的问题
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
关于16位数据的读写，这里有两点需要说明：
1. 由于risc-v使用的是小端存储，而且是以16位为包块进行的小端存储
x86的机器也是小端存储，但是内存的读写是以8位为包，所以我们需要
对指令的存储进行一次交叉处理，具体见代码。
2. 是否为符号数只跟res有关，如果res是uhalfword类型则是无符号数，
若是halfword类型则只是有符号数。
*/

uhalfword read_mem_uhalfword(uword addr)
{
	ubyte *p = (uhalfword *)(mem + addr);
	uhalfword res = 0;
	res = (*(p + 1) + (*(p) << 8));			//指令读取的交叉处理
	return res;
}

void write_mem_uhalfword(uword addr, uhalfword val)
{
	ubyte *p = (uhalfword *)(mem + addr);
	ubyte val1 = val;
	ubyte val2 = val >> 8;
	*(p) = val2;							//指令存储的交叉处理
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
关于32位数据的读写，这里有两点需要说明：
1. 由于risc-v使用的是小端存储，而且是以16位为包块进行的小端存储
x86的机器也是小端存储，但是内存的读写是以8位为包，所以我们需要
对指令的存储进行两次交叉处理，具体见代码。
2. 是否为符号数只跟res有关，如果res是uword类型则是无符号数，
若是word类型则只是有符号数。
*/

//在这里犯了个错误导致debug了一天。。
//之前声明p指针的时候使用的是uword类型，后来跑程序的时候发现读取下一条指令的时候总是不对
//于是进行各种单步测试，知道最后才发现是这个p指针类型的问题
//如果声明是uword类型，则指针指向的数据占32位，那么p+1其实是下一个32位数据
//然而交叉处理是分别将8位数据进行交换，这里如果错误的使用了uword类型那么就将8位数据存到相邻的几个32位空间中了
//这么必然是错误的
//启示我们编程的时候一定要小心。。。。
uword read_mem_uword(uword addr)
{
	ubyte *p = (ubyte *)(mem + addr);
	uword res = 0;
	res = ((*(p + 2) << 24) + (*(p + 3) << 16) + (*(p) << 8) + *(p + 1));		//指令读取的交叉处理
	return res;
}

void write_mem_uword(uword addr, uword val)
{
	ubyte *p = (ubyte *)(mem + addr);
	ubyte val1 = val;
	ubyte val2 = val >> 8;
	ubyte val3 = val >> 16;
	ubyte val4 = val >> 24;
	*(p) = val2;							//指令存储的交叉处理
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