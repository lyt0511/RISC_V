#include <stdio.h>
#include <stdlib.h>
#include "variable.h"

//�Ĵ����ļ��Ķ�д����
uword get_uint(uword addr)
{
	return *((uword *)(reg + addr));
}

void put_uint(uword addr, uword val)
{
	*((uword *)(reg + addr)) = val;
}

word get_int(uword addr)
{
	return *((word *)(reg + addr));
}

void put_int(uword addr, word val)
{
	*((word *)(reg + addr)) = val;
}