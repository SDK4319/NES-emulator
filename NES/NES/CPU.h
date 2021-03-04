#pragma once
#include"Header.h"


//Processor: MOS 6502
class CPU
{
public:
	CPU();
	~CPU();

	//Registers
	ui8		a		= 0x00;	// Accumulator
	ui8		x		= 0x00;	// X reg
	ui8		y		= 0x00; // Y reg
	ui8		sp		= 0x00; // Stack Pointer
	ui16	pc		= 0x0000; // Program Counter
	ui8		status	= 0x00; // Status

	void clock();
	void reset();
	void irq();		//Interrupt Request
	void nmi();		// Non-Maskable IRQ
	bool complete();

	void setBus(Bus* bus) { this->bus = bus; }

	std::map<ui16, std::string> disassemble(ui16 nStart, ui16 nStop);



	enum FLAGS6502 {
		C = (1 << 0),	// Carry Bit
		Z = (1 << 1),	// Zero
		I = (1 << 2),	// Disable Interrupts
		D = (1 << 3),	// Decimal Mode (unused in NES)
		B = (1 << 4),	// Break
		U = (1 << 5),	// Unused in NES
		V = (1 << 6),	// Overflow
		N = (1 << 7),	// Negative
	};

private:

	ui8 GetFlag(FLAGS6502 f);
	void SetFlag(FLAGS6502 f, bool v);

	ui8 fetched = 0x00;
	ui16 temp = 0x0000;
	ui16 addr_abs = 0x0000;
	ui16 addr_rel = 0x0000;
	ui8 opcode = 0x00;
	ui8 cycles = 0x00;
	ui32 clock_count = 0;

	Bus* bus = nullptr;

	ui8 read(ui16 addr);
	void write(ui16 addr, ui8 data);

	ui8 fetch();

	struct INSTRUCTION {
		std::string name;
		ui8 (CPU::*operate)(void) = nullptr;
		ui8 (CPU::*addrmode)(void) = nullptr;
		ui8 cycles = 0;
	};

	std::vector<INSTRUCTION> lookup;

private: // Addressing Modes
	ui8 IMP();	
	ui8 IMM();
	ui8 ZP0();	
	ui8 ZPX();
	ui8 ZPY();	
	ui8 REL();
	ui8 ABS();	
	ui8 ABX();
	ui8 ABY();	
	ui8 IND();
	ui8 IZX();	
	ui8 IZY();

private: // Opcodes
	ui8 ADC();	
	ui8 AND();	
	ui8 ASL();	
	ui8 BCC();
	ui8 BCS();	
	ui8 BEQ();	
	ui8 BIT();	
	ui8 BMI();
	ui8 BNE();	
	ui8 BPL();	
	ui8 BRK();	
	ui8 BVC();
	ui8 BVS();	
	ui8 CLC();	
	ui8 CLD();	
	ui8 CLI();
	ui8 CLV();	
	ui8 CMP();	
	ui8 CPX();	
	ui8 CPY();
	ui8 DEC();	
	ui8 DEX();	
	ui8 DEY();	
	ui8 EOR();
	ui8 INC();	
	ui8 INX();	
	ui8 INY();	
	ui8 JMP();
	ui8 JSR();	
	ui8 LDA();	
	ui8 LDX();	
	ui8 LDY();
	ui8 LSR();	
	ui8 NOP();	
	ui8 ORA();	
	ui8 PHA();
	ui8 PHP();	
	ui8 PLA();	
	ui8 PLP();	
	ui8 ROL();
	ui8 ROR();	
	ui8 RTI();	
	ui8 RTS();	
	ui8 SBC();
	ui8 SEC();	
	ui8 SED();	
	ui8 SEI();	
	ui8 STA();
	ui8 STX();	
	ui8 STY();	
	ui8 TAX();	
	ui8 TAY();
	ui8 TSX();	
	ui8 TXA();	
	ui8 TXS();	
	ui8 TYA();
	// Unofficial OPCode
	ui8 XXX();

};

