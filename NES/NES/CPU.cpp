#include "Header.h"

CPU::CPU()
{
	using a = CPU;
	lookup =
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}

CPU::~CPU()
{
}

uint8_t CPU::read(uint16_t addr)
{
	return bus->cpuRead(addr, false);
}

void CPU::write(uint16_t addr, uint8_t data)
{
	bus->cpuWrite(addr, data);
}

void CPU::clock() {
	if (cycles == 0) {
		opcode = read(pc);

		SetFlag(U, true);

		pc++;

		cycles = lookup[opcode].cycles;
		uint8_t cycle1 = (this->*lookup[opcode].addrmode)();
		uint8_t cycle2 = (this->*lookup[opcode].operate)();

		cycles += (cycle1 & cycle2);
		SetFlag(U, true);
	}
	clock_count++;
	cycles--;
}

void CPU::reset() {
	addr_abs = 0xFFFC;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;

	a = 0x00;
	x = 0x00;
	y = 0x00;
	sp = 0xFD;
	status = 0x00 | U;

	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;

	cycles = 8;
}

void CPU::irq() {
	if (GetFlag(I) == 0) {
		//push the pc to the stack
		write(0x0100 + sp, (pc >> 8) & 0x00FF);
		sp--;
		write(0x0100 + sp, pc & 0x00FF);
		sp--;

		//push the status register to the stack
		SetFlag(B, 0);
		SetFlag(U, 1);
		SetFlag(I, 1);
		write(0x0100 + sp, status);
		sp--;

		//read new pc from fixed address
		addr_abs = 0xFFFE;
		uint16_t lo = read(addr_abs + 0);
		uint16_t hi = read(addr_abs + 1);
		pc = (hi << 8) | lo;

		cycles = 7;
	}
}

void CPU::nmi() {
	write(0x0100 + sp, (pc >> 8) & 0x00FF);
	sp--;
	write(0x0100 + sp, pc & 0x00FF);
	sp--;

	SetFlag(B, 0);
	SetFlag(U, 1);
	SetFlag(I, 1);
	write(0x0100 + sp, status);
	sp--;

	addr_abs = 0xFFFA;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;

	cycles = 8;
}

uint8_t CPU::GetFlag(FLAGS6502 f) {
	return ((status & f) > 0) ? 1 : 0;
}

void CPU::SetFlag(FLAGS6502 f, bool v) {
	if (v)
		status |= f;
	else
		status &= ~f;
}

// Addressing Modes 
uint8_t CPU::IMP() {
	fetched = a;
	return 0;
}
uint8_t CPU::IMM() {
	addr_abs = pc++;
	return 0;
}
uint8_t CPU::ZP0() {
	addr_abs = read(pc);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}
uint8_t CPU::ZPX() {
	addr_abs = (read(pc) + x);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}
uint8_t CPU::ZPY() {
	addr_abs = (read(pc) + y);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}
uint8_t CPU::REL() {
	addr_rel = read(pc);
	pc++;
	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;
	return 0;
}
uint8_t CPU::ABS() { //Absolut
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;
	addr_abs = (hi << 8) | lo;
	return 0;
}
uint8_t CPU::ABX() { //Absolut + x 
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;
	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}
uint8_t CPU::ABY() { //Absolut + y
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;
	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}
uint8_t CPU::IND() {
	uint16_t ptr_lo = read(pc);
	pc++;
	uint16_t ptr_hi = read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo = 0x00FF)
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	else
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
	return 0;
}
uint8_t CPU::IZX() {
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;

	return 0;
}
uint8_t CPU::IZY() {
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}


uint8_t CPU::fetch()
{
	if (!(lookup[opcode].addrmode == &CPU::IMP))
		fetched = read(addr_abs);
	return fetched;
}

// Instructions
// �� �̰� �ʹ�������
uint8_t CPU::ADC()
{
	fetch();
	temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C);
	SetFlag(C, temp > 255);
	SetFlag(Z, (temp & 0x00FF) == 0);
	SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp)) & 0x0080);
	SetFlag(N, temp & 0x80);
	a = temp & 0x00FF;

	return 1;
}
uint8_t CPU::SBC()
{
	fetch();
	uint16_t value = ((uint16_t)fetched) ^ 0x00FF;

	temp = (uint16_t)a + value + (uint16_t)GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, ((temp & 0x00FF) == 0));
	SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
	SetFlag(N, temp & 0x0080);
	a = temp & 0x00FF;
	return 1;
}
uint8_t CPU::AND()
{
	fetch();
	a = a & fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}
uint8_t CPU::ASL()
{
	fetch();
	temp = (uint16_t)fetched << 1;
	SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}
uint8_t CPU::BCC()
{
	if (GetFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::BCS()
{
	if (GetFlag(C) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::BEQ()
{
	if (GetFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::BIT()
{
	fetch();
	temp = a & fetched;
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, fetched & (1 << 7));
	SetFlag(V, fetched & (1 << 6));
	return 0;
}
uint8_t CPU::BMI()
{
	if (GetFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::BNE()
{
	if (GetFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::BPL()
{
	if (GetFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::BRK()
{
	pc++;

	SetFlag(I, 1);
	write(0x0100 + sp, (pc >> 8) & 0x00FF);
	sp--;
	write(0x0100 + sp, pc & 0x00FF);
	sp--;

	SetFlag(B, 1);
	write(0x0100 + sp, status);
	sp--;
	SetFlag(B, 0);

	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
	return 0;
}
uint8_t CPU::BVC()
{
	if (GetFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::BVS()
{
	if (GetFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}
uint8_t CPU::CLC()
{
	SetFlag(C, false);
	return 0;
}
uint8_t CPU::CLD()
{
	SetFlag(D, false);
	return 0;
}
uint8_t CPU::CLI()
{
	SetFlag(I, false);
	return 0;
}
uint8_t CPU::CLV()
{
	SetFlag(V, false);
	return 0;
}
uint8_t CPU::CMP()
{
	fetch();
	temp = (uint16_t)a - (uint16_t)fetched;
	SetFlag(C, a >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 1;
}
uint8_t CPU::CPX()
{
	fetch();
	temp = (uint16_t)x - (uint16_t)fetched;
	SetFlag(C, x >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}
uint8_t CPU::CPY()
{
	fetch();
	temp = (uint16_t)y - (uint16_t)fetched;
	SetFlag(C, y >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}
uint8_t CPU::DEC()
{
	fetch();
	temp = fetched - 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}
uint8_t CPU::DEX()
{
	x--;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}
uint8_t CPU::DEY()
{
	y--;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}
uint8_t CPU::EOR()
{
	fetch();
	a = a ^ fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}
uint8_t CPU::INC()
{
	fetch();
	temp = fetched + 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}
uint8_t CPU::INX()
{
	x++;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}
uint8_t CPU::INY()
{
	y++;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}
uint8_t CPU::JMP()
{
	pc = addr_abs;
	return 0;
}
uint8_t CPU::JSR()
{
	pc--;

	write(0x0100 + sp, (pc >> 8) & 0x00FF);
	sp--;
	write(0x0100 + sp, pc & 0x00FF);
	sp--;

	pc = addr_abs;
	return 0;
}
uint8_t CPU::LDA()
{
	fetch();
	a = fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}
uint8_t CPU::LDX()
{
	fetch();
	x = fetched;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 1;
}
uint8_t CPU::LDY()
{
	fetch();
	y = fetched;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 1;
}

uint8_t CPU::LSR()
{
	fetch();
	SetFlag(C, fetched & 0x0001);
	temp = fetched >> 1;
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t CPU::NOP()
{
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}
uint8_t CPU::ORA()
{
	fetch();
	a = a | fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}
uint8_t CPU::PHA()
{
	write(0x0100 + sp, a);
	sp--;
	return 0;
}
uint8_t CPU::PHP()
{
	write(0x0100 + sp, status | B | U);
	SetFlag(B, 0);
	SetFlag(U, 0);
	sp--;
	return 0;
}
uint8_t CPU::PLA()
{
	sp++;
	a = read(0x0100 + sp);
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}
uint8_t CPU::PLP()
{
	sp++;
	status = read(0x0100 + sp);
	SetFlag(U, 1);
	return 0;
}
uint8_t CPU::ROL()
{
	fetch();
	temp = (uint16_t)(fetched << 1) | GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}
uint8_t CPU::ROR()
{
	fetch();
	temp = (uint16_t)(GetFlag(C) << 7) | (fetched >> 1);
	SetFlag(C, fetched & 0x01);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &CPU::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}
uint8_t CPU::RTI()
{
	sp++;
	status = read(0x0100 + sp);
	status &= ~B;
	status &= ~U;

	sp++;
	pc = (uint16_t)read(0x0100 + sp);
	sp++;
	pc |= (uint16_t)read(0x0100 + sp) << 8;
	return 0;
}
uint8_t CPU::RTS()
{
	sp++;
	pc = (uint16_t)read(0x0100 + sp);
	sp++;
	pc |= (uint16_t)read(0x0100 + sp) << 8;

	pc++;
	return 0;
}
uint8_t CPU::SEC()
{
	SetFlag(C, true);
	return 0;
}
uint8_t CPU::SED()
{
	SetFlag(D, true);
	return 0;
}
uint8_t CPU::SEI()
{
	SetFlag(I, true);
	return 0;
}
uint8_t CPU::STA()
{
	write(addr_abs, a);
	return 0;
}
uint8_t CPU::STX()
{
	write(addr_abs, x);
	return 0;
}
uint8_t CPU::STY()
{
	write(addr_abs, y);
	return 0;
}
uint8_t CPU::TAX()
{
	x = a;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}
uint8_t CPU::TAY()
{
	y = a;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}
uint8_t CPU::TSX()
{
	x = sp;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}
uint8_t CPU::TXA()
{
	a = x;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}
uint8_t CPU::TXS()
{
	sp = x;
	return 0;
}
uint8_t CPU::TYA()
{
	a = y;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU::XXX()
{
	return 0;
}





///////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS

bool CPU::complete()
{
	return cycles == 0;
}
std::map<uint16_t, std::string> CPU::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		std::string sInst = "$" + hex(addr, 4) + ": ";

		uint8_t opcode = bus->cpuRead(addr, true); addr++;
		sInst += lookup[opcode].name + " ";
		if (lookup[opcode].addrmode == &CPU::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrmode == &CPU::IMM)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZP0)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZPX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZPY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrmode == &CPU::IZX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrmode == &CPU::IZY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABS)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrmode == &CPU::IND)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrmode == &CPU::REL)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + value, 4) + "] {REL}";
		}

		mapLines[line_addr] = sInst;
	}

	return mapLines;

}