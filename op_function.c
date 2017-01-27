#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "variable.h"

//����ָ��ִ��(��)

uword INSN_LUI(long PC)
{
	word *rd = reg + RD;
	*rd = U_IMM;
	printf("��ʼִ��LUIָ��(U��ָ��)��������U_IMM = 0x%x\n", U_IMM);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC+4);
	return PC + 4;
}

uword INSN_AUIPC(long PC)
{
	word *rd = reg + RD;
	*rd = PC + U_IMM;
	printf("��ʼִ��AUIPCָ��(U��ָ��)��������U_IMM = 0x%x\n", U_IMM);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_JAL(long PC)
{
	word *rd = reg + RD;
	*rd = PC + 4;			//�ӳ���ͨ���Ĵ���rd�ĵ�ַ����
	printf("��ʼִ��JALָ��(UJ��ָ��)��������UJ_IMM = 0x%x\n", UJ_IMM);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + UJ_IMM);
	return PC + UJ_IMM;
}

uword INSN_JALR(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = PC + 4;
	printf("��ʼִ��JALRָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, (rs1 + I_IMM) & 0xfffffffe);
	return ((rs1 + I_IMM) & 0xfffffffe);   //���λ��0
}

uword INSN_BEQ(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("��ʼִ��BEQָ��(SB��ָ��)��������SB_IMM = 0x%x, Դ������rs1 = %d,  Դ������rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 == rs2)
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BNE(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("��ʼִ��BNEָ��(SB��ָ��)��������SB_IMM = 0x%x, Դ������rs1 = %d,  Դ������rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 != rs2)
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BLT(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("��ʼִ��BLTָ��(SB��ָ��)��������SB_IMM = 0x%x, Դ������rs1 = %d,  Դ������rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 < rs2)
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BGE(long PC)
{
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("��ʼִ��BGEָ��(SB��ָ��)��������SB_IMM = 0x%x, Դ������rs1 = %d,  Դ������rs2 = %d\n", SB_IMM, rs1, rs2);
	if (rs1 > rs2)
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BLTU(long PC)
{
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	printf("��ʼִ��BLTUָ��(SB��ָ��)��������SB_IMM = 0x%x, Դ������rs1 = 0x%x,  Դ������rs2 = 0x%x\n", SB_IMM, rs1, rs2);
	if (rs1 < rs2)
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_BGEU(long PC)
{
	uword rs1 = get_int(RS1);
	uword rs2 = get_int(RS2);
	printf("��ʼִ��BGEUָ��(SB��ָ��)��������SB_IMM = 0x%x, Դ������rs1 = 0x%x,  Դ������rs2 = 0x%x\n", SB_IMM, rs1, rs2);
	if (rs1 > rs2)
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + SB_IMM);
		return PC + SB_IMM;
	}
	else
	{
		printf("ִ�н��: NextPC = 0x%x\n", PC + 4);
		return PC + 4;
	}
}

uword INSN_LB(long PC)
{
	uword rs = 0;
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;				//���ʣ������I������Ӧ�����з��ŵĻ����޷��ŵ�
	ubyte tmp = (ubyte)read_mem_ubyte(addr);	//�ѽ����������չָ�ľ����з�����������չָ�����޷�����
	if (tmp >> 7)							//�ԴӴ洢��ȡ����8λ�����з�����չ
		rs = (uword)tmp | 0xffffff00;
	else
		rs = (word)tmp;
	*rd = rs;
	printf("��ʼִ��LBָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LH(long PC)
{
	uword rs = 0;
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	uhalfword tmp = (uhalfword)read_mem_uhalfword(addr);
	if (tmp >> 15)							//�ԴӴ洢��ȡ����16λ�����з�����չ
		rs = (uword)tmp | 0xffff0000;
	else
		rs = (word)tmp;
	*rd = rs;
	printf("��ʼִ��LHָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LW(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	word rs = read_mem_word(addr);
	*rd = rs;
	printf("��ʼִ��LWָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LBU(long PC)
{
	uword *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;				//���ʣ������I������Ӧ�����з��ŵĻ����޷��ŵ�
	ubyte rs = read_mem_ubyte(addr);	//�ѽ����������չָ�ľ����з�����������չָ�����޷�����
	*rd = rs;
	printf("��ʼִ��LBUָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_LHU(long PC)
{
	uword *rd = reg + RD;
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	uhalfword rs = read_mem_uhalfword(addr);
	*rd = rs;
	printf("��ʼִ��LHUָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

//SB��SH��������޷�����
//������һ����Ҫע�⣬printf %x��ʽ�������ʽ��int�����
//����������з�����������Ǹ�����������з�����չΪint����
//������޷���������ô���������ת��������ת��Ϊ�޷�����
uword INSN_SB(long PC)
{
	word rs1 = get_int(RS1);
	word addr = rs1 + S_IMM;
	byte rs2 = (get_int(RS2) & 0xff);
	write_mem_byte(addr, rs2);
	printf("��ʼִ��SBָ��(S��ָ��)��������S_IMM = 0x%x, Դ������rs1 = %d\n, Դ������rs2 = %d\n", S_IMM, rs1, rs2);
	printf("ִ�н��: MEM[rs1+S_IMM] = 0x%x, NextPC = 0x%x\n", (ubyte)read_mem_byte(addr), PC + 4);
	return PC + 4;
}

uword INSN_SH(long PC)
{
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	halfword rs2 = (get_int(RS2) & 0xffff);
	write_mem_halfword(addr, rs2);
	printf("��ʼִ��SHָ��(S��ָ��)��������S_IMM = 0x%x, Դ������rs1 = %d\n, Դ������rs2 = %d\n", S_IMM, rs1, rs2);
	printf("ִ�н��: MEM[rs1+S_IMM] = 0x%x, NextPC = 0x%x\n", (uhalfword)read_mem_halfword(addr), PC + 4);
	return PC + 4;
}

uword INSN_SW(long PC)
{
	word rs1 = get_int(RS1);
	word addr = rs1 + I_IMM;
	word rs2 = get_int(RS2);
	write_mem_word(addr, rs2);
	printf("%x\n", rs2);
	printf("��ʼִ��SWָ��(S��ָ��)��������S_IMM = 0x%x, Դ������rs1 = %d\n, Դ������rs2 = %d\n", S_IMM, rs1, rs2);
	printf("ִ�н��: MEM[rs1+S_IMM] = 0x%x, NextPC = 0x%x\n", (uword)read_mem_word(addr), PC + 4);
	return PC + 4;
}

uword INSN_ADDI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 + I_IMM;
	printf("��ʼִ��ADDIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLTI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	printf("��ʼִ��STLIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = %d\n", I_IMM, rs1);
	if (rs1 < I_IMM)
	{
		*rd = 1;
		printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	else
	{
		*rd = 0;
		printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	return PC + 4;
}

uword INSN_SLTIU(long PC)
{
	word *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword uimm = (uword)I_UIMM;
	printf("��ʼִ��SLTIUָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = 0x%x\n", I_IMM, rs1);
	if (I_IMM == 1)				//��ָ��SLTIU rd, rs1, 1�Ĵ���
		if (rs1 == 0)
		{
			*rd = 1;
			printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	else
		if (rs1 < uimm)
		{
			*rd = 1;
			printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	return PC + 4;
}

uword INSN_XORI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 ^ I_IMM;
	printf("��ʼִ��XORIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = 0x%x\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_ORI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 | I_IMM;
	printf("��ʼִ��ORIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = 0x%x\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_ANDI(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	*rd = rs1 & I_IMM;
	printf("��ʼִ��ANDIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = 0x%x\n", I_IMM, rs1);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLLI(long PC)
{
	uword *rd = reg + RD;		
	uword rs1 = get_uint(RS1);
	int cnt = I_UIMM & 0x1f;	
	*rd = rs1 << cnt;			//������Ҫ˵һ�£�c���Ե��������߼�����
	printf("��ʼִ��SLLIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = 0x%x\n, ��λ����cnt = %d", I_IMM, rs1, cnt);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;				//Ȼ��ʵ������������=�߼�����
}

uword INSN_SRLI(long PC)
{
	uword *rd = reg + RD;		
	uword rs1 = get_uint(RS1);
	int cnt = I_UIMM & 0x1f;	
	*rd = rs1 >> cnt;			//c���Ե��������������ƣ����ұ߲��Ϸ�����
	printf("��ʼִ��SRLIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = 0x%x\n, ��λ����cnt = %d", I_IMM, rs1, cnt);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;				//Ȼ��ʵ�����߼����ƺ��������Ʋ�һ�����߼������ǲ�0�����Խ���������ת��Ϊ�޷������ٽ������ƾ����߼�����
}

uword INSN_SRAI(long PC)
{
	word *rd = reg + RD;		
	word rs1 = get_int(RS1);
	int cnt = I_UIMM & 0x1f;	
	*rd = rs1 >> cnt;
	printf("��ʼִ��SRAIָ��(I��ָ��)��������I_IMM = 0x%x, Դ������rs1 = 0x%x\n, ��λ����cnt = %d", I_IMM, rs1, cnt);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_ADD(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	*rd = rs1 + rs2;
	printf("��ʼִ��ADDָ��(R��ָ��)��Դ������rs1 = %d, Դ������rs2 = %d\n", rs1, rs2);
	printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SUB(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	*rd = rs1 - rs2;
	printf("��ʼִ��SUBָ��(R��ָ��)��Դ������rs1 = %d, Դ������rs2 = %d\n", rs1, rs2);
	printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLL(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	int cnt = rs2 & 0x1f;
	*rd = rs1 << cnt;
	printf("��ʼִ��SLLָ��(R��ָ��)��Դ������rs1 = 0x%x, Դ������rs2 = 0x%x\n, ��λ����cnt = %d", rs1, rs2, cnt);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SLT(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	word rs2 = get_int(RS2);
	printf("��ʼִ��SLTָ��(R��ָ��)��Դ������rs1 = %d, Դ������rs2 = %d\n", rs1, rs2);
	if (rs1 < rs2)
	{
		*rd = 1;
		printf("ִ�н��: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	else
	{
		*rd = 0;
		printf("ִ�н��: RD = %x, REG[RD] = %d, NextPC = 0x%x\n", RD, *rd, PC + 4);
	}
	return PC + 4;
}

uword INSN_SLTU(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	printf("��ʼִ��SLTUָ��(R��ָ��)��Դ������rs1 = 0x%x, Դ������rs2 = 0x%x\n", rs1, rs2);
	if (rs1 == 0)					//��ָ��SLTU rd, x0, rs2�Ĵ���
		if (rs2 != 0)
		{
			*rd = 1;
			printf("ִ�н��: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("ִ�н��: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	else
		if (rs1 < rs2)
		{
			*rd = 1;
			printf("ִ�н��: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
		else
		{
			*rd = 0;
			printf("ִ�н��: RD = %x, REG[RD] = %d NextPC = 0x%x\n", RD, *rd, PC + 4);
		}
	return PC + 4;
}

uword INSN_XOR(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	*rd = rs1 ^ rs2;
	printf("��ʼִ��XORָ��(R��ָ��)��Դ������rs1 = 0x%x, Դ������rs2 = 0x%x\n", rs1, rs2);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SRL(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	int cnt = rs2 & 0x1f;
	*rd = rs1 >> cnt;
	printf("��ʼִ��SRLָ��(R��ָ��)��Դ������rs1 = 0x%x, Դ������rs2 = 0x%x\n, ��λ����cnt = %d", rs1, rs2, cnt);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_SRA(long PC)
{
	word *rd = reg + RD;
	word rs1 = get_int(RS1);
	uword rs2 = get_uint(RS2);
	int cnt = rs2 & 0x1f;
	*rd = rs1 >> cnt;
	printf("��ʼִ��SRAָ��(R��ָ��)��Դ������rs1 = 0x%x, Դ������rs2 = 0x%x\n, ��λ����cnt = %d", rs1, rs2, cnt);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_OR(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	*rd = rs1 | rs2;
	printf("��ʼִ��ORָ��(R��ָ��)��Դ������rs1 = 0x%x, Դ������rs2 = 0x%x\n", rs1, rs2);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_AND(long PC)
{
	uword *rd = reg + RD;
	uword rs1 = get_uint(RS1);
	uword rs2 = get_uint(RS2);
	*rd = rs1 & rs2;
	printf("��ʼִ��ANDָ��(R��ָ��)��Դ������rs1 = 0x%x, Դ������rs2 = 0x%x\n", rs1, rs2);
	printf("ִ�н��: RD = %x, REG[RD] = 0x%x, NextPC = 0x%x\n", RD, *rd, PC + 4);
	return PC + 4;
}

uword INSN_FENCE(long PC)
{
	printf("ִ��FENCEָ��\n");
	return PC + 4;
}

uword INSN_FENCE_I(long PC)
{
	printf("ִ��FENCE_Iָ��\n");
	return PC + 4;
}

uword INSN_ECALL(long PC)
{
	printf("ִ��ECALLָ��\n");
	return PC + 4;
}

uword INSN_EBREAK(long PC)
{
	printf("ִ��EBREAKָ��\n");
	return PC + 4;
}

uword INSN_CSRRW(long PC)
{
	if (RD == 0)						//��RDΪx0���򲻶�CSRֱ������
	{
		printf("��ʼִ��CSRRRWָ�Ŀ�ļĴ���RD=X0���ʲ���ȡCSR������");
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
		printf("��ʼִ��CSRRWָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
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
	if (RS1 == 0)							//��RS1Ϊx0����дSRֱ������
	{
		printf("��ʼִ��CSRRSָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = csr_old | rs1;
		printf("��ʼִ��CSRRSָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
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
	if (RS1 == 0)							//��RS1Ϊx0����дCSRֱ������
	{
		printf("��ʼִ��CSRRSָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = ~(~csr_old | rs1);
		printf("��ʼִ��CSRRSָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		*csr = rs1;
		return PC + 4;
	}
}

uword INSN_CSRRWI(long PC)
{
	if (RD == 0)						//��RDΪx0���򲻶�CSRֱ������
	{
		printf("��ʼִ��CSRRRWIָ�Ŀ�ļĴ���RD=X0���ʲ���ȡCSR������");
		return PC + 4;
	}
	else
	{
		uword *rd = reg + RD;
		uword *csr = reg + CSR;
		uword csr_old = get_uint(CSR);
		uword rs1 = (uword)RS1;			//CSRRXIϵ��ָ���RS1�ֶ���������
		*rd = csr_old;
		*csr = rs1;
		printf("��ʼִ��CSRRWIָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
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
	if (RS1 == 0)							//��RS1Ϊ0����дSRֱ������
	{
		printf("��ʼִ��CSRRSIָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = csr_old | rs1;
		printf("��ʼִ��CSRRSIָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
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
	if (RS1 == 0)							//��RS1Ϊ0����дCSRֱ������
	{
		printf("��ʼִ��CSRRCIָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
	else
	{
		*csr = ~(~csr_old | rs1);
		printf("��ʼִ��CSRRCIָ�Դ������rs1 = 0x%x, �Ĵ���CSRֵ = 0x%x\n", rs1, csr_old);
		printf("ִ�н��: RD = %x, REG[RD] = 0x%x, REG[CSR] = 0x%x, NextPC = 0x%x\n", RD, *rd, *csr, PC + 4);
		return PC + 4;
	}
}