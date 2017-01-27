#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "variable.h"

//具体指令执行(改)

uword INSN_LUI(long PC)
{
	word *rd = reg + RD;
	*rd = U_IMM;
	printf("开始执行LUI指令(U类指令)：立即数U_IMM = 0x%x\n", U_IMM);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC+4);
	return PC + 4;
}

uword INSN_AUIPC(long PC)
{
	word *rd = reg + RD;
	*rd = PC + U_IMM;
	printf("开始执行AUIPC指令(U类指令)：立即数U_IMM = 0x%x\n", U_IMM);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_JAL(long PC)
{
	word *rd = reg + RD;
	*rd = PC + 4;			//子程序通过寄存器rd的地址返回
	printf("开始执行JAL指令(UJ类指令)：立即数UJ_IMM = 0x%x\n", UJ_IMM);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + UJ_IMM);
	return PC + UJ_IMM;
}

uword INSN_JALR(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = PC + 4;
	printf("开始执行JALR指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, (rs1 + I_IMM) & 0xfffffffe);
	return ((rs1 + I_IMM) & 0xfffffffe);   //最低位置0
}

uword INSN_BEQ(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("开始执行BEQ指令(SB类指令)：立即数SB_IMM = 0x%x, 源操作数rs1 = %d,  源操作数rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 == rs2)
	{
		printf("执行结果: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("执行结果: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BNE(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("开始执行BNE指令(SB类指令)：立即数SB_IMM = 0x%x, 源操作数rs1 = %d,  源操作数rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 != rs2)
	{
		printf("执行结果: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("执行结果: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BLT(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("开始执行BLT指令(SB类指令)：立即数SB_IMM = 0x%x, 源操作数rs1 = %d,  源操作数rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 < rs2)
	{
		printf("执行结果: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("执行结果: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BGE(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("开始执行BGE指令(SB类指令)：立即数SB_IMM = 0x%x, 源操作数rs1 = %d,  源操作数rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 > rs2)
	{
		printf("执行结果: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("执行结果: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BLTU(long PC)
{
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	printf("开始执行BLTU指令(SB类指令)：立即数SB_IMM = 0x%x, 源操作数rs1 = 0x%x,  源操作数rs2 = 0x%x\n", SB_IMM, rs1, rs2);
	if (rs1 < rs2)
	{
		printf("执行结果: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("执行结果: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BGEU(long PC)
{
	uword rs1 = get_int(RS1);
	uword rs2 = get_int(RS2);
	printf("开始执行BGEU指令(SB类指令)：立即数SB_IMM = 0x%x, 源操作数rs1 = 0x%x,  源操作数rs2 = 0x%x\n", SB_IMM, rs1, rs2);
	if (rs1 > rs2)
	{
		printf("执行结果: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("执行结果: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_LB(long PC)
{
	uword rs = 0;
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;				//疑问：这里的I立即数应该是有符号的还是无符号的
	ubyte tmp = (ubyte)read_mem_ubyte(addr);	//已解决，符号扩展指的就是有符号数，零扩展指的是无符号数
	if (tmp >> 7)							//对从存储器取出的8位数进行符号扩展
		rs = (uword)tmp | 0xffffff00;
	else
		rs = (word)tmp;
	*rd = rs;
	printf("开始执行LB指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LH(long PC)
{
	uword rs = 0;
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	uhalfword tmp = (uhalfword)read_mem_uhalfword(addr);
	if (tmp >> 15)							//对从存储器取出的16位数进行符号扩展
		rs = (uword)tmp | 0xffff0000;
	else
		rs = (word)tmp;
	*rd = rs;
	printf("开始执行LH指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LW(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	word rs = read_mem_word(addr);
	*rd = rs;
	printf("开始执行LW指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LBU(long PC)
{
	uword *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;				//疑问：这里的I立即数应该是有符号的还是无符号的
	ubyte rs = read_mem_ubyte(addr);	//已解决，符号扩展指的就是有符号数，零扩展指的是无符号数
	*rd = rs;
	printf("开始执行LBU指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LHU(long PC)
{
	uword *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	uhalfword rs = read_mem_uhalfword(addr);
	*rd = rs;
	printf("开始执行LHU指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

//SB和SH存入的是无符号数
//这里有一点需要注意，printf %x格式是输出格式是int，如果
//待输出数是有符号数，如果是负数，则会自行符号扩展为int类型
//如果是无符号数，那么会进行两次转换，最终转换为无符号数
uword INSN_SB(long PC)
{
	word rs1 = get_int(RS1);
	word addr = rs1 + S_IMM;
	byte rs2 = (get_int(RS2) & 0xff);
	write_mem_byte(addr, rs2);
	printf("开始执行SB指令(S类指令)：立即数S_IMM = 0x%x, 源操作数rs1 = %d\n, 源操作数rs2 = %d\n", S_IMM, rs1, rs2);
	printf("执行结果: MEM[rs1+S_IMM] = 0x%x, NextPC = 0x%x\n", (ubyte)read_mem_byte(addr), PC + 4);
	return PC + 4;
}

uword INSN_SH(long PC)
{
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	halfword rs2 = (get_int(RS2) & 0xffff);
	write_mem_halfword(addr, rs2);
	printf("开始执行SH指令(S类指令)：立即数S_IMM = 0x%x, 源操作数rs1 = %d\n, 源操作数rs2 = %d\n", S_IMM, rs1, rs2);
	printf("执行结果: MEM[rs1+S_IMM] = 0x%x, NextPC = 0x%x\n", (uhalfword)read_mem_halfword(addr), PC + 4);
	return PC + 4;
}

uword INSN_SW(long PC)
{
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	word rs2 = get_int(RS2);
	write_mem_word(addr, rs2);
	printf("%x\n", rs2);
	printf("开始执行SW指令(S类指令)：立即数S_IMM = 0x%x, 源操作数rs1 = %d\n, 源操作数rs2 = %d\n", S_IMM, rs1, rs2);
	printf("执行结果: MEM[rs1+S_IMM] = 0x%x, NextPC = 0x%x\n", (uword)read_mem_word(addr), PC + 4);
	return PC + 4;
}

uword INSN_ADDI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 + I_IMM;
	printf("开始执行ADDI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLTI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	printf("开始执行STLI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = %d\n", I_IMM, rs1);
	if (rs1 < I_IMM)
	{
		*rd = 1;
		printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	else
	{
		*rd = 0;
		printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	return PC + 4;
}

uword INSN_SLTIU(long PC)
{
	word *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword uimm = (uword)I_UIMM;
	printf("开始执行SLTIU指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = 0x%x\n", I_IMM, rs1);
	if (I_IMM == 1)				//对指令SLTIU rd, rs1, 1的处理
		if (rs1 == 0)
		{
			*rd = 1;
			printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	else
		if (rs1 < uimm)
		{
			*rd = 1;
			printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	return PC + 4;
}

uword INSN_XORI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 ^ I_IMM;
	printf("开始执行XORI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = 0x%x\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_ORI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 | I_IMM;
	printf("开始执行ORI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = 0x%x\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_ANDI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 & I_IMM;
	printf("开始执行ANDI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = 0x%x\n", I_IMM, rs1);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLLI(long PC)
{
	uword *rd = reg + RD;		
	uword rs1 = get_uint(RS1);
	int cnt = I_UIMM & 0x1f;	
	*rd = rs1 << cnt;			//这里需要说一下，c语言的左移是逻辑左移
	printf("开始执行SLLI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = 0x%x\n, 移位次数cnt = %d", I_IMM, rs1, cnt);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;				//然而实际中算数左移=逻辑左移
}

uword INSN_SRLI(long PC)
{
	uword *rd = reg + RD;		
	uword rs1 = get_uint(RS1);
	int cnt = I_UIMM & 0x1f;	
	*rd = rs1 >> cnt;			//c语言的右移是算术左移，即右边补上符号数
	printf("开始执行SRLI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = 0x%x\n, 移位次数cnt = %d", I_IMM, rs1, cnt);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;				//然而实际中逻辑右移和算术右移不一样，逻辑右移是补0，所以将被操作数转换为无符号数再进行右移就是逻辑右移
}

uword INSN_SRAI(long PC)
{
	word *rd = reg + RD;		
	word rs1 = get_int(RS1);
	int cnt = I_UIMM & 0x1f;	
	*rd = rs1 >> cnt;
	printf("开始执行SRAI指令(I类指令)：立即数I_IMM = 0x%x, 源操作数rs1 = 0x%x\n, 移位次数cnt = %d", I_IMM, rs1, cnt);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_ADD(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	*rd = rs1 + rs2;
	printf("开始执行ADD指令(R类指令)：源操作数rs1 = %d, 源操作数rs2 = %d\n", rs1, rs2);
	printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SUB(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	*rd = rs1 - rs2;
	printf("开始执行SUB指令(R类指令)：源操作数rs1 = %d, 源操作数rs2 = %d\n", rs1, rs2);
	printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLL(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	int cnt = rs2 & 0x1f;
	*rd = rs1 << cnt;
	printf("开始执行SLL指令(R类指令)：源操作数rs1 = 0x%x, 源操作数rs2 = 0x%x\n, 移位次数cnt = %d", rs1, rs2, cnt);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLT(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("开始执行SLT指令(R类指令)：源操作数rs1 = %d, 源操作数rs2 = %d\n", rs1, rs2);
	if (rs1 < rs2)
	{
		*rd = 1;
		printf("执行结果: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	else
	{
		*rd = 0;
		printf("执行结果: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	return PC + 4;
}

uword INSN_SLTU(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	printf("开始执行SLTU指令(R类指令)：源操作数rs1 = 0x%x, 源操作数rs2 = 0x%x\n", rs1, rs2);
	if (rs1 == 0)					//对指令SLTU rd, x0, rs2的处理
		if (rs2 != 0)
		{
			*rd = 1;
			printf("执行结果: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("执行结果: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	else
		if (rs1 < rs2)
		{
			*rd = 1;
			printf("执行结果: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("执行结果: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	return PC + 4;
}

uword INSN_XOR(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	*rd = rs1 ^ rs2;
	printf("开始执行XOR指令(R类指令)：源操作数rs1 = 0x%x, 源操作数rs2 = 0x%x\n", rs1, rs2);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SRL(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	int cnt = rs2 & 0x1f;
	*rd = rs1 >> cnt;
	printf("开始执行SRL指令(R类指令)：源操作数rs1 = 0x%x, 源操作数rs2 = 0x%x\n, 移位次数cnt = %d", rs1, rs2, cnt);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SRA(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	uword rs2 = get_uint(RS2);
	int cnt = rs2 & 0x1f;
	*rd = rs1 >> cnt;
	printf("开始执行SRA指令(R类指令)：源操作数rs1 = 0x%x, 源操作数rs2 = 0x%x\n, 移位次数cnt = %d", rs1, rs2, cnt);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_OR(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	*rd = rs1 | rs2;
	printf("开始执行OR指令(R类指令)：源操作数rs1 = 0x%x, 源操作数rs2 = 0x%x\n", rs1, rs2);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_AND(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	*rd = rs1 & rs2;
	printf("开始执行AND指令(R类指令)：源操作数rs1 = 0x%x, 源操作数rs2 = 0x%x\n", rs1, rs2);
	printf("执行结果: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_FENCE(long PC)
{
	printf("执行FENCE指令\n");
	return PC + 4;
}

uword INSN_FENCE_I(long PC)
{
	printf("执行FENCE_I指令\n");
	return PC + 4;
}

uword INSN_ECALL(long PC)
{
	printf("执行ECALL指令\n");
	return PC + 4;
}

uword INSN_EBREAK(long PC)
{
	printf("执行EBREAK指令\n");
	return PC + 4;
}

uword INSN_CSRRW(long PC)
{
	if (RD == 0)						//若RD为x0，则不读CSR直接跳过
	{
		printf("开始执行CSRRRW指令：目的寄存器RD=X0，故不读取CSR并跳过");
		return PC + 4;
	}
	else
	{
		uword *rd = reg + RD;
		uword *csr = reg + CSR;
		uword csr_old = get_uint(CSR);
		uword rs1 = get_uint(RS1);
		*rd = csr_old;
		*csr = rs1;
		printf("开始执行CSRRW指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
}

uword INSN_CSRRS(long PC)
{
	uword *rd = reg + RD;
	uword *csr = reg + CSR;
	uword csr_old = get_uint(CSR);
	uword rs1 = get_uint(RS1);
	*rd = csr_old;
	if (RS1 == 0)							//若RS1为x0，则不写SR直接跳过
	{
		printf("开始执行CSRRS指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = csr_old | rs1;
		printf("开始执行CSRRS指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
}

uword INSN_CSRRC(long PC)
{
	uword *rd = reg + RD;
	uword *csr = reg + CSR;
	uword csr_old = get_uint(CSR);
	uword rs1 = get_uint(RS1);
	*rd = csr_old;
	if (RS1 == 0)							//若RS1为x0，则不写CSR直接跳过
	{
		printf("开始执行CSRRS指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = ~(~csr_old | rs1);
		printf("开始执行CSRRS指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		*csr = rs1;
		return PC + 4;
	}
}

uword INSN_CSRRWI(long PC)
{
	if (RD == 0)						//若RD为x0，则不读CSR直接跳过
	{
		printf("开始执行CSRRRWI指令：目的寄存器RD=X0，故不读取CSR并跳过");
		return PC + 4;
	}
	else
	{
		uword *rd = reg + RD;
		uword *csr = reg + CSR;
		uword csr_old = get_uint(CSR);
		uword rs1 = (uword)RS1;			//CSRRXI系列指令的RS1字段是立即数
		*rd = csr_old;
		*csr = rs1;
		printf("开始执行CSRRWI指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
}

uword INSN_CSRRSI(long PC)
{
	uword *rd = reg + RD;
	uword *csr = reg + CSR;
	uword csr_old = get_uint(CSR);
	uword rs1 = (uword)RS1;
	*rd = csr_old;
	if (RS1 == 0)							//若RS1为0，则不写SR直接跳过
	{
		printf("开始执行CSRRSI指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = csr_old | rs1;
		printf("开始执行CSRRSI指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
}

uword INSN_CSRRCI(long PC)
{
	uword *rd = reg + RD;
	uword *csr = reg + CSR;
	uword csr_old = get_uint(CSR);
	uword rs1 = (uword)RS1;
	*rd = csr_old;
	if (RS1 == 0)							//若RS1为0，则不写CSR直接跳过
	{
		printf("开始执行CSRRCI指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = ~(~csr_old | rs1);
		printf("开始执行CSRRCI指令：源操作数rs1 = 0x%x, 寄存器CSR值 = 0x%x\n", rs1, csr_old);
		printf("执行结果: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
}