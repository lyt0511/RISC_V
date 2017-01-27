#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "variable.h"

mem_size = 0x080000;
reg_size = 32;

main()
{
	//内存和寄存器文件的空间分配
	if ((mem = (char *)malloc(sizeof(char)*mem_size)) == NULL)
	{
		printf("Error : Memory allocation\n");
		exit(-1);
	}

	if ((reg = (int *)malloc(sizeof(int)*reg_size)) == NULL)
	{
		printf("Error : RegFile allocation\n");
		exit(-1);
	}

	memset(mem, 0, sizeof(char)*mem_size);
	memset(reg, 0, sizeof(int)*reg_size);

	uword addr = 256, a0 = 1;

	int i1 = 15, i2 = -34, i3 = 0, i4;
	uword u1 = 0x5, u2 = 0xf0000001, u3 = 0, u4;
	//load和store单条指令测试，需要向存储器中事先存储数据
	write_mem_byte(0x0010, 0x81);				//8位数据
	write_mem_halfword(0x0011, 0x8171);			//16位数据
	write_mem_word(0x0013, 0x80008171);			//32位数据

	//指定寄存器:RD = R1, RS1 = R2, RS2 = R3 uR2和uR3是源操作数的无符号数版本
	int R0 = 0, R1 = 1, R2 = 2, R3 = 3, R4 = 7, uR2 = 4, uR3 = 5, uR4 = 6, csr = 8;

	put_int(R0, 0);
	put_int(R2, i1);
	put_int(R3, i2);
	put_int(R4, i3);
	put_uint(uR2, u1);
	put_uint(uR3, u2);
	put_uint(uR4, u3);
	put_uint(csr, 0x123);

	//单指令测试

	//write_mem_uword(0x1000, 0xf00010b7);		//mem[0x1000] = LUI R1, 0xf0001000(U_IMM)
	//write_mem_uword(0x1000, 0x00001097);		//mem[0x1000] = AUIPC R1, 0x00001000(U_IMM)

	//在JAL指令处测试UJ立即数的符号扩展的正确性(20位)
	//write_mem_uword(0x1000, 0x004000ef);		//mem[0x1000] = JAL R1, 0x000004(J_IMM)
	//write_mem_uword(0x1000, 0x804000ef);		//mem[0x1000] = JAL R1, 0x080004(J_IMM)	

	//在JALR指令处测试I立即数的符号扩展的正确性(12位)
	//write_mem_uword(0x1000, 0x001100e7);		//mem[0x1000] = JALR R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x801100e7);		//mem[0x1000] = JALR R1, R2, 0x000801(I_IMM)

	//在BEQ指令处测试SB立即数的符号扩展的正确性(12位)
	//write_mem_uword(0x1000, 0x00310163);		//mem[0x1000] = BEQ R2, R3, 0x000002(B_IMM)
	//write_mem_uword(0x1000, 0x80310163);		//mem[0x1000] = BEQ R2, R3, 0x000802(B_IMM)

	//write_mem_uword(0x1000, 0x00311163);		//mem[0x1000] = BNE R2, R3, 0x000002(B_IMM)

	//BLT有两条测试指令，第一条中rs1>rs2，第二条中rs1<rs2
	//write_mem_uword(0x1000, 0x00314163);		//mem[0x1000] = BLT R2, R3, 0x000002(B_IMM)
	//write_mem_uword(0x1000, 0x0021c163);		//mem[0x1000] = BLT R2, R3, 0x000002(B_IMM)

	//write_mem_uword(0x1000, 0x00315163);		//mem[0x1000] = BGE R2, R3, 0x000002(B_IMM)

	//BLTU有两条测试指令，由于变为无符号数的比较，所以第一条中rs1<rs2，第二条中rs1>rs2
	//write_mem_uword(0x1000, 0x00526163);		//mem[0x1000] = BLTU uR2, uR3, 0x000002(B_IMM)
	//write_mem_uword(0x1000, 0x0042e163);		//mem[0x1000] = BLTU uR2, uR3, 0x000002(B_IMM)

	//write_mem_uword(0x1000, 0x00527163);		//mem[0x1000] = BGEU uR2, uR3, 0x000002(B_IMM)
	//write_mem_uword(0x1000, 0x00110083);		//mem[0x1000] = LB R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00211083);		//mem[0x1000] = LH R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00412083);		//mem[0x1000] = LW R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00114083);		//mem[0x1000] = LBU R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00215083);		//mem[0x1000] = LHU R1, R2, 0x000001(I_IMM)

	////在SB指令处测试S立即数的符号扩展的正确性(12位)
	//write_mem_uword(0x1000, 0x003100a3);		//mem[0x1000] = SB R2, R3, 0x000001(S_IMM)
	//write_mem_uword(0x1000, 0x803100a3);		//mem[0x1000] = SB R2, R3, 0x000801(S_IMM)

	//write_mem_uword(0x1000, 0x003111a3);		//mem[0x1000] = SH R2, R3, 0x000001(S_IMM)
	//write_mem_uword(0x1000, 0x003120a3);		//mem[0x1000] = SW R2, R3, 0x000001(S_IMM)
	//write_mem_uword(0x1000, 0x00110093);		//mem[0x1000] = ADDI R1, R2, 0x000001(I_IMM)

	//SLT有两条测试指令，第一条中rs1>I_IMM，第二条中rs1<I_IMM
	//write_mem_uword(0x1000, 0x00112093);		//mem[0x1000] = SLTI R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x001012093);		//mem[0x1000] = SLTI R1, R2, 0x000010(I_IMM)

	//STLIU有四条测试指令，前两条分别是I_UIMM为1的情况，后两条分别是I_UIMM不为1的情况(rs1>I_UIMM, rs1<I_UIMM)
	//write_mem_uword(0x1000, 0x00123093);		//mem[0x1000] = SLTIU R1, uR2(rs1!=0), 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00133093);		//mem[0x1000] = SLTIU R1, uR4(rs1=0), 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00223093);		//mem[0x1000] = SLTIU R1, uR2, 0x000002(I_IMM)
	//write_mem_uword(0x1000, 0x00623093);		//mem[0x1000] = SLTIU R1, uR1, 0x000006(I_IMM)

	//XORI有两条测试指令，第一条是I_IMM不为-1的情况，后一条是I_IMM为-1的情况
	//write_mem_uword(0x1000, 0x00114093);		//mem[0x1000] = XORI R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0xfff14093);		//mem[0x1000] = XORI R1, R2, -1(I_IMM)
	
	//write_mem_uword(0x1000, 0x00116093);		//mem[0x1000] = ORI R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00117093);		//mem[0x1000] = ANDI R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x00111093);		//mem[0x1000] = SLLI R1, R2, 0x000001(I_IMM)

	//SRLI有两条测试指令，第一条中源操作数是正数，符号位为0，第二条是负数，符号位为1
	//write_mem_uword(0x1000, 0x00115093);		//mem[0x1000] = SRLI R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x0011d093);		//mem[0x1000] = SRLI R1, R3, 0x000001(I_IMM)

	//SRAI有两条测试指令，第一条中源操作数是正数，符号位为0，第二条是负数，符号位为1
	//write_mem_uword(0x1000, 0x40115093);		//mem[0x1000] = SRAI R1, R2, 0x000001(I_IMM)
	//write_mem_uword(0x1000, 0x4011d093);		//mem[0x1000] = SRAI R1, R3, 0x000001(I_IMM)

	//write_mem_uword(0x1000, 0x003100b3);		//mem[0x1000] = ADD R1, R2, R3
	//write_mem_uword(0x1000, 0x403100b3);		//mem[0x1000] = SUB R1, R2, R3
	//write_mem_uword(0x1000, 0x003110b3);		//mem[0x1000] = SLL R1, R2, R3

	//SLT有两条测试指令，第一条中rs1>rs2，第二条中rs1<rs2
	//write_mem_uword(0x1000, 0x003120b3);		//mem[0x1000] = SLT R1, R2, R3
	//write_mem_uword(0x1000, 0x0021a0b3);		//mem[0x1000] = SLT R1, R3, R2

	//SLTU有四条测试指令，前两条中rs1=R0，一条rs2=0,另一条rs2!=0;后两条中rs1!=R0,一条rs1>rs2，另一条中rs1<rs2
	//write_mem_uword(0x1000, 0x007030b3);		//mem[0x1000] = SLTU R1, R0, R4
	//write_mem_uword(0x1000, 0x003030b3);		//mem[0x1000] = SLTU R1, R0, R3
	//write_mem_uword(0x1000, 0x003130b3);		//mem[0x1000] = SLTU R1, R2, R3
	//write_mem_uword(0x1000, 0x0021b0b3);		//mem[0x1000] = SLTU R1, R3, R2

	//write_mem_uword(0x1000, 0x003140b3);		//mem[0x1000] = XOR R1, R2, R3

	//由于SRL和SRA与之前的两个位移指令类似，所以不做展开测试,不过请一起去掉指定代码的注释
	//put_int(R4, 3);                           //指定代码，修改位移寄存器的值
	//write_mem_uword(0x1000, 0x007150b3);		//mem[0x1000] = SRL R1, R2, R3
	//write_mem_uword(0x1000, 0x4071d0b3);		//mem[0x1000] = SRA R1, R3, R3

	//write_mem_uword(0x1000, 0x003160b3);		//mem[0x1000] = OR R1, R2, R3
	//write_mem_uword(0x1000, 0x003170b3);		//mem[0x1000] = AND R1, R2, R3
	//write_mem_uword(0x1000, 0x0000000f);		//mem[0x1000] = FENCE
	//write_mem_uword(0x1000, 0x0000100f);		//mem[0x1000] = FENCE_I
	//write_mem_uword(0x1000, 0x00000073);		//mem[0x1000] = ECALL
	//write_mem_uword(0x1000, 0x00100073);		//mem[0x1000] = EBREAK
	//write_mem_uword(0x1000, 0x008110f3);		//mem[0x1000] = CSRRW R1, R2, CSR
	//write_mem_uword(0x1000, 0x008120f3);		//mem[0x1000] = CSRRS R1, R2, CSR
	//write_mem_uword(0x1000, 0x008130f3);		//mem[0x1000] = CSRRC R1, R2, CSR
	//write_mem_uword(0x1000, 0x0083d0f3);		//mem[0x1000] = CSRRWI R1, 0x7, CSR
	//write_mem_uword(0x1000, 0x0083e0f3);		//mem[0x1000] = CSRRSI R1, 0x7, CSR
	//write_mem_uword(0x1000, 0x0083f0f3);		//mem[0x1000] = CSRRCI R1, 0x7, CSR

	//多指令测试
	/*
	write_mem_word(0x0013, 0x5);
	write_mem_word(0x0017, 0x6);
	put_int(R4, 11);

	write_mem_uword(0x1000, 0x01302103);		//mem[0x1000] = LW R2, R0, 0x0013
	write_mem_uword(0x1004, 0x01702183);		//mem[0x1004] = LW R3, R0, 0x0017
	write_mem_uword(0x1008, 0x003100b3);		//mem[0x1008] = ADD R1, R2, R3
	write_mem_uword(0x100c, 0x02708063);		//mem[0x100c] = BEQ R1, R4, 0x20
	write_mem_uword(0x102c, 0x001029a3);		//mem[0x1020] = SW R1, R0, 0x0013
	*/

	Execution();

	i3 = get_int(R1);
	u3 = get_uint(R1);
	printf("最终结果：RD = %d, REG[RD] = 0x%x, uREG[RD] = 0x%x\n", RD, i3, u3);

	/*
	//内存读写测试
	uword addr = 256, a0 = 1;
	uword ur;
	word r;

	ubyte ub1, ub2;
	ub1 = 0xf5;
	write_mem_ubyte(addr, ub1);
	ub2 = read_mem_ubyte(addr);
	put_uint(a0, ub1);
	ur = get_uint(a0);
	printf("ubyte1 = %u, ubyte2 = %u, r_uint = %u\n", ub1, ub2, ur);

	byte b1, b2;
	b1 = 0xf5;
	write_mem_byte(addr, b1);
	b2 = read_mem_byte(addr);
	put_int(a0, b1);
	r = get_int(a0);
	printf("byte1 = %i, byte2 = %i, r_int = %i\n", b1, b2, r);

	uhalfword uh1, uh2;
	uh1 = 0xc3f5;
	write_mem_uhalfword(addr, uh1);
	uh2 = read_mem_uhalfword(addr);
	put_uint(a0, uh1);
	ur = get_uint(a0);
	printf("uhalfword1 = %u, uhalfword2 = %u, r_uint = %u\n", uh1, uh2, ur);

	halfword h1, h2;
	h1 = 0xc3f5;
	write_mem_halfword(addr, h1);
	h2 = read_mem_halfword(addr);
	put_int(a0, h1);
	r = get_int(a0);
	printf("halfword1 = %i, halfword2 = %i, r_int = %i\n", h1, h2, r);

	uword uw1, uw2;
	uw1 = 0xe2a6c3f5;
	write_mem_uword(addr, uw1);
	uw2 = read_mem_uword(addr);
	put_uint(a0, uw1);
	ur = get_uint(a0);
	printf("uword1 = %u, uword2 = %u, r_uint = %u\n", uw1, uw2, ur);

	word w1, w2;
	w1 = 0xe2a6c3f5;
	write_mem_word(addr, w1);
	w2 = read_mem_word(addr);
	put_int(a0, w1);
	r = get_int(a0);
	printf("word1 = %i, word2 = %i, r_int = %i\n", w1, w2, r);

	float f1, f2;
	f1 = 256.0625;
	write_mem_float(addr, f1);
	f2 = read_mem_float(addr);
	printf("float1 = %f, float2 = %f\n", f1, f2);


	double d1, d2;
	d1 = 256.0625;
	write_mem_double(addr, d1);
	d2 = read_mem_double(addr);
	printf("double1 = %f, double2 = %f\n", d1, d2);
	*/

	/*
	int i1 = 16, i2 = -35, i3;
	put_int(2, i1);       // R2 = 16
	put_int(3, i2);       // R3 = -35
	write_mem_uword(0x1000, 0x00430800);  // mem[0x1000] = ADD R1, R2, R3
	write_mem_uword(0x1004, 0x8c000000);  // mem[0x1004] = JR R0
	Execution();       // execution above two MIPS instructions
	i3 = get_int(1);
	printf("r1 = %d\n", i3);     // output the value of R1
	*/

	getchar();

	free(mem);
	free(reg);
}
