#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "variable.h"

//��ʼ��ָ�����룬��ø����ֶ�
void initDecode(uword insn)
{
	//���������Ĵ����ֶ�
	OPCODE = insn & 0x7f;
	RD = (insn >> 7) & 0x1f;
	FUNCT3 = (insn >> 12) & 0x7;
	RS1 = (insn >> 15) & 0x1f;
	RS2 = (insn >> 20) & 0x1f;
	FUNCT7 = (insn >> 25) & 0x7f;
	CSR = (insn >> 20) & 0xfff;

	//�������ֶΣ��ֱ���I��S��SB��U��UJ����������
	if ((insn >> 31))
		I_IMM = (int)((insn >> 20) & 0xfff) | 0xfffff000;						//I������������չ
	else
		I_IMM = (int)((insn >> 20) & 0xfff);
	I_UIMM = (uword)((insn >> 20) & 0xfff);
	uword S1_IMM = (insn >> 31) & 0x1;
	uword S2_IMM = (insn >> 25) & 0x3f;
	uword S3_IMM = (insn >> 8) & 0xf;
	uword S4_IMM = (insn >> 7) & 0x1;
	if (S1_IMM)
		S_IMM = (int)((S1_IMM << 11) + (S2_IMM << 5) + (S3_IMM << 1) + S4_IMM) | 0xfffff000;									//S������������չ
	else
		S_IMM = (int)((S1_IMM << 11) + (S2_IMM << 5) + (S3_IMM << 1) + S4_IMM);

	//printf("%x\n", S_IMM);
	S_UIMM = (uword)((S1_IMM << 11) + (S2_IMM << 5) + (S3_IMM << 1) + S4_IMM);
	if (S1_IMM)
		SB_IMM = (int)((S1_IMM << 12) + (S4_IMM << 11) + (S2_IMM << 5) + (S3_IMM << 1)) | 0xffffe000;							//B������������չ
	else
		SB_IMM = (int)((S1_IMM << 12) + (S4_IMM << 11) + (S2_IMM << 5) + (S3_IMM << 1));
	SB_UIMM = (uword)((S1_IMM << 12) + (S4_IMM << 11) + (S2_IMM << 5) + (S3_IMM << 1));
	U_IMM = (int)(((insn >> 12) & 0xfffff) << 12);
	uword UJ1_IMM = (insn >> 31) & 0x1;
	uword UJ2_IMM = (insn >> 25) & 0x3f;
	uword UJ3_IMM = (insn >> 21) & 0xf;
	uword UJ4_IMM = (insn >> 20) & 0x1;
	uword UJ5_IMM = (insn >> 12) & 0xff;
	if (UJ1_IMM)
		UJ_IMM = (int)((UJ1_IMM << 20) + (UJ5_IMM << 12) + (UJ4_IMM << 11) + (UJ2_IMM << 5) + (UJ3_IMM << 1)) | 0xffe00000;		//J������������չ
	else
		UJ_IMM = (int)((UJ1_IMM << 20) + (UJ5_IMM << 12) + (UJ4_IMM << 11) + (UJ2_IMM << 5) + (UJ3_IMM << 1));
	UJ_UIMM = (uword)((UJ1_IMM << 20) + (UJ5_IMM << 12) + (UJ4_IMM << 11) + (UJ2_IMM << 5) + (UJ3_IMM << 1));

	//���ڲ�ָͬ����������Ҫ���ֶ�
	printf("R��ָ�� :OPCODE = 0x%x, FUNCT3 = 0x%x, FUNCT7 = 0x%x, RD = 0x%x, RS1 = 0x%x, RS2 = 0x%x\n", OPCODE, FUNCT3, FUNCT7, RD, RS1, RS2);
	printf("I��ָ�� :OPCODE = 0x%x, FUNCT3 = 0x%x, RD = 0x%x, RS1 = 0x%x, I_IMM = 0x%x, I_UIMM = 0x%x\n", OPCODE, FUNCT3, RD, RS1, I_IMM, I_UIMM);
	printf("S��ָ�� :OPCODE = 0x%x, FUNCT3 = 0x%x, RS1 = 0x%x, RS2 = 0x%x, S_IMM = 0x%x, S_UIMM = 0x%x\n", OPCODE, FUNCT3, RS1, RS2, S_IMM, S_UIMM);
	printf("SB��ָ��:OPCODE = 0x%x, FUNCT3 = 0x%x, RS1 = 0x%x, RS2 = 0x%x, SB_IMM = 0x%x, SB_UIMM = 0x%x\n", OPCODE, FUNCT3, RS1, RS2, SB_IMM, SB_UIMM);
	printf("U��ָ�� :OPCODE = 0x%x, RD = 0x%x, U_IMM = 0x%x\n",OPCODE, RD, U_IMM);
	printf("UJ��ָ��:OPCODE = 0x%x, RD = 0x%x, UJ_IMM = 0x%x, UJ_UIMM = 0x%x\n\n", OPCODE, RD, UJ_IMM, UJ_UIMM);
}