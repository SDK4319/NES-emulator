#pragma once
#include<vector>
#include<map>
#include<functional>
#include<memory>
#include"Rom.h"
#include"MapperInterface.h"

enum IORegisters {
	PPUCTRL = 0x2000,
	PPUMASK,
	PPUSTATUS,
	OAMADDR,
	OAMDATA,
	PPUSCROL,
	PPUADDR,
	PPUDATA,
	OAMDMA = 0x4014,
	JOY1 = 0x4016,
	JOY2 = 0x4017,
};

class MainBus
{
public:
	MainBus();
	byte read(Addr addr);
	void write(Addr addr, byte value);
	bool setMapper(Mapper* mapper);
	bool setWriteCallback(IORegisters reg, std::function<void(byte)> callback);
	bool setReadCallback(IORegisters reg, std::function<byte(void)> callback);
	byte* getPagePtr(byte page);

private:
	std::vector<byte> m_RAM;
	std::vector<byte> m_extRAM;
	Mapper* m_mapper;

	std::map<IORegisters, std::function<void(byte)>> m_writeCallbacks;
	std::map<IORegisters, std::function<byte(void)>> m_readCallbacks;
};

