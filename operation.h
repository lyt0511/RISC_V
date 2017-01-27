#pragma once
#ifndef OP_H
#define OP_H

enum opcodes
{
	/* All R-Type Insns are SPECIAL insns: Opcode = 0  */
	OP_SPECIAL = 0,

	OP_LOAD = 3,        //����ָ���
	OP_FENCE = 15,		//FENCEָ���
	OP_COMPU_I = 19,	//����������ָ���
	OP_AUIPC = 23,
	OP_STORE = 35,		//����ָ���
	OP_COMPU = 51,		//����ָ���
	OP_LUI = 55,
	OP_BRANCH = 99,		//��ָ֧���
	OP_JALR = 103,
	OP_JAL = 111,
	OP_SYSTEM = 115,	//ϵͳָ���
						/* !!! Do *NOT* remove this entry !!!
						This is used to delimit the end of the opcode array, so we can check
						to see if you try to define more that 64 opcodes!
						*/
						//NUM_OPCODES
};

enum branches
{
	OP_BEQ,
	OP_BNE,
	OP_BLT = 4,
	OP_BGE,
	OP_BLTU,
	OP_BGEU,
	/* !!! Do *NOT* remove this entry !!!
	This is used to delimit the end of the function array, so we can check
	to see if you try to define more that 2048 functions!
	*/
	//NUM_FUNCS
};

enum loads
{
	OP_LB,
	OP_LH,
	OP_LW,
	OP_LBU = 4,
	OP_LHU,
	/* !!! Do *NOT* remove this entry !!!
	This is used to delimit the end of the function array, so we can check
	to see if you try to define more that 2048 functions!
	*/
	//NUM_FUNCS
};

enum stores
{
	OP_SB,
	OP_SH,
	OP_SW,
	/* !!! Do *NOT* remove this entry !!!
	This is used to delimit the end of the function array, so we can check
	to see if you try to define more that 2048 functions!
	*/
	//NUM_FUNCS
};

enum computation_i
{
	OP_ADDI,
	OP_SLLI,
	OP_SLTI,
	OP_SLTIU,
	OP_XORI,
	OP_SRI,		//����SRLI��SRAI,��FUNCT7����
	OP_ORI,
	OP_ANDI,
	/* !!! Do *NOT* remove this entry !!!
	This is used to delimit the end of the function array, so we can check
	to see if you try to define more that 2048 functions!
	*/
	//NUM_FUNCS
};

enum computation
{
	OP_ADDSUB,	//����ADD��SUB����FUNCT7����
	OP_SLL,
	OP_SLT,
	OP_SLTU,
	OP_XOR,
	OP_SR,		//����SRL��SRA����FUNCT7����
	OP_OR,
	OP_AND,
	/* !!! Do *NOT* remove this entry !!!
	This is used to delimit the end of the function array, so we can check
	to see if you try to define more that 2048 functions!
	*/
	//NUM_FUNCS
};

enum systems
{
	OP_ECB,		//����ECALL��EBREAKָ���FUNCT7+RS2����
	OP_CSRRW,
	OP_CSRRS,
	OP_CSRRC,
	OP_CSRRWI = 5,
	OP_CSRRSI,
	OP_CSRRCI,
	/* !!! Do *NOT* remove this entry !!!
	This is used to delimit the end of the function array, so we can check
	to see if you try to define more that 2048 functions!
	*/
	//NUM_FUNCS
};

#endif