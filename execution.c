#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "variable.h"


//取指令，指令译码以及执行(改)
void Execution(void)
{
	PC = 0x1000;
	for (; PC;)
	{
		//处理PC越界情况
		if (PC >= sizeof(char)*mem_size || PC < 0x1000)
		{
			printf("错误: PC越界，指令终止\n");
			return;
		}

		uword insn = read_mem_uword(PC);

		//指令译码
		printf("----------------------------------------------------------\n");
		printf("PC = 0x%X, INSTRUCTION = 0x%X\n\n", PC, insn);
		initDecode(insn); 
		if (OPCODE)
		{
			switch (OPCODE)
			{
			case OP_LUI: PC = INSN_LUI(PC); break;
			case OP_AUIPC: PC = INSN_AUIPC(PC); break;
			case OP_JAL: PC = INSN_JAL(PC); break;
			case OP_JALR: PC = INSN_JALR(PC); break;
			case OP_BRANCH:
				switch (FUNCT3)
				{
				case OP_BEQ: PC = INSN_BEQ(PC); break;
				case OP_BNE: PC = INSN_BNE(PC); break;
				case OP_BLT: PC = INSN_BLT(PC); break;
				case OP_BGE: PC = INSN_BGE(PC); break;
				case OP_BLTU: PC = INSN_BLTU(PC); break;
				case OP_BGEU: PC = INSN_BGEU(PC); break;
				}
				break;
			case OP_LOAD:
				switch (FUNCT3)
				{
				case OP_LB: PC = INSN_LB(PC); break;
				case OP_LH: PC = INSN_LH(PC); break;
				case OP_LW: PC = INSN_LW(PC); break;
				case OP_LBU: PC = INSN_LBU(PC); break;
				case OP_LHU: PC = INSN_LHU(PC); break;
				}
				break;
			case OP_STORE:
				switch (FUNCT3)
				{
				case OP_SB: PC = INSN_SB(PC); break;
				case OP_SH: PC = INSN_SH(PC); break;
				case OP_SW: PC = INSN_SW(PC); break;
				}
				break;
			case OP_COMPU_I:
				switch (FUNCT3)
				{
				case OP_ADDI: PC = INSN_ADDI(PC); break;
				case OP_SLTI: PC = INSN_SLTI(PC); break;
				case OP_SLTIU: PC = INSN_SLTIU(PC); break;
				case OP_XORI: PC = INSN_XORI(PC); break;
				case OP_ORI: PC = INSN_ORI(PC); break;
				case OP_ANDI: PC = INSN_ANDI(PC); break;
				case OP_SLLI: PC = INSN_SLLI(PC); break;
				case OP_SRI:
					if (FUNCT7 == 0)
						PC = INSN_SRLI(PC);
					else
						PC = INSN_SRAI(PC);
					break;
				}
				break;
			case OP_COMPU:
				switch (FUNCT3)
				{
				case OP_ADDSUB:
					if (FUNCT7 == 0)
						PC = INSN_ADD(PC);
					else
						PC = INSN_SUB(PC);
					break;
				case OP_SLL: PC = INSN_SLL(PC); break;
				case OP_SLT: PC = INSN_SLT(PC); break;
				case OP_SLTU: PC = INSN_SLTU(PC); break;
				case OP_XOR: PC = INSN_XOR(PC); break;
				case OP_SR:
					if (FUNCT7 == 0)
						PC = INSN_SRL(PC);
					else
						PC = INSN_SRA(PC);
					break;
				case OP_OR: PC = INSN_OR(PC); break;
				case OP_AND: PC = INSN_AND(PC); break;
				}
				break;
			case OP_FENCE:
				if (FUNCT3 == 0)
					PC = INSN_FENCE(PC);
				else
					PC = INSN_FENCE_I(PC);
				break;
			case OP_SYSTEM:
				switch (FUNCT3)
				{
				case OP_ECB:
					if (RS2 == 0)				//注意再检查一下
						PC = INSN_ECALL(PC);
					else
						PC = INSN_EBREAK(PC);
					break;
				case OP_CSRRW: PC = INSN_CSRRW(PC); break;
				case OP_CSRRS: PC = INSN_CSRRS(PC); break;
				case OP_CSRRC: PC = INSN_CSRRC(PC); break;
				case OP_CSRRWI: PC = INSN_CSRRWI(PC); break;
				case OP_CSRRSI: PC = INSN_CSRRSI(PC); break;
				case OP_CSRRCI: PC = INSN_CSRRCI(PC); break;
				}
				break;
			default: printf("错误 : PC - 0x%X 不是可以执行的指令\n", PC); 
				     printf("----------------------------------------------------------\n");
				     return;
			}
		}
		else
		{
			printf("测试结束, PC = 0x%X\n", PC);
			printf("----------------------------------------------------------\n");
			return;
		}

		printf("----------------------------------------------------------\n");

		/*
		if (OPCODE)		//若不是R指令
		{
		switch (OPCODE)
		{
		case OP_ADDI: PC = INSN_ADDI(PC); break;
		case OP_ADDUI: PC = INSN_ADDUI(PC); break;
		case OP_NOP: PC = INSN_NOP(PC); break;
		case OP_JR: PC = INSN_JR(PC); break;
		default: printf("Error: Unimplemented instruction\n"); exit(-1);
		}
		}
		else           //若是R指令
		{
		switch (FUNC)
		{
		case OP_ADD: PC = INSN_ADD(PC); break;
		case OP_ADDU: PC = INSN_ADDU(PC); break;
		default: printf("Error : Unimplemented instruction\n"); exit(-1);
		}
		}
		*/
	}
}