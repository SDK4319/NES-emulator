#pragma once

#include"MainBus.h"

class CPU
{
public:
	enum InterruptType {
		IRQ,
		NMI,
		BRK_
	};

	CPU(MainBus& mem);

	void interrupt(InterruptType type);

	void step();
	void reset();
	void reset(Addr start_addr);
	void log();

	Addr getPC() { return r_PC; }
	void skipDMACycles();

private:
	//Instructions are split info five sets to make decoding easier
	//These functions return true if they succeed
	bool executeImplied(byte opcode);
	bool executeBranch(byte opcode);
	bool executeType0(byte opcode);
	bool executeType1(byte opcode);
	bool executeType2(byte opcode);

	Addr readAddress(Addr addr);

	void pushStack(byte value);
	byte pullStack();

	void setPageCrossed(Addr a, Addr b, int inc = 1);
	void setZN(byte value);

	int m_skipCycles;
	int m_cycles;

	//Registers
	Addr r_PC;
	byte r_SP;
	byte r_A;
	byte r_X;
	byte r_Y;

	bool f_C;
	bool f_Z;
	bool f_I;

	bool f_D;
	bool f_V;
	bool f_N;

	MainBus& m_bus;
};

