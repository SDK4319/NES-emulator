#include "MapperCNROM.h"

MapperCNROM::MapperCNROM(Rom& cart) :
	Mapper(cart, Mapper::CNROM),
	m_selectCHR(0)
{
	m_oneBank = (cart.getRom().size() == 0x4000);
}

void MapperCNROM::writePRG(Addr addr, byte value)
{
	m_selectCHR = value & 0x3;
}

byte MapperCNROM::readPRG(Addr addr)
{
	if (!m_oneBank)
		return m_cartridge.getRom()[addr - 0x8000];
	else
		return m_cartridge.getRom()[(addr - 0x8000) & 0x3fff];
}

byte* MapperCNROM::getPagePtr(Addr addr)
{
	if (!m_oneBank)
		return &m_cartridge.getRom()[addr - 0x8000];
	else
		return &m_cartridge.getRom()[(addr - 0x8000) & 0x3fff];
}

byte MapperCNROM::readCHR(Addr addr)
{
	return m_cartridge.getVRom()[addr | (m_selectCHR << 13)];
}

void MapperCNROM::writeCHR(Addr addr, byte value)
{
	std::cout << "Read-only CHR memory write attempt at " << std::hex << addr << std::endl;
}
