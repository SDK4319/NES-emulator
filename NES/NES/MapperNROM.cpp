#include "MapperNROM.h"

MapperNROM::MapperNROM(Rom& cart) :
    Mapper(cart, Mapper::NROM)
{
    m_oneBank = (cart.getRom().size() == 0x4000);

    if (cart.getVRom().size() == 0) {
        m_usesCharacterRam = true;
        m_characterRam.resize(0x2000);
        std::cout << "Uses character Ram" << std::endl;
    }
    else {
        m_usesCharacterRam = false;
    }
}

void MapperNROM::writePRG(Addr addr, byte value)
{
    std::cout << "ROM Memory write attempt at " << +addr << " to set " << +value << std::endl;
}

byte MapperNROM::readPRG(Addr addr)
{
    if (!m_oneBank) 
        return m_cartridge.getRom()[addr - 0x8000];
    else
        return m_cartridge.getRom()[(addr - 0x8000) & 0x3fff];
}

byte* MapperNROM::getPagePtr(Addr addr)
{
    if (!m_oneBank)
        return &m_cartridge.getRom()[addr - 0x8000];
    else
        return &m_cartridge.getRom()[(addr - 0x8000) & 0x3fff];
}

byte MapperNROM::readCHR(Addr addr)
{

    if (m_usesCharacterRam)
        return m_characterRam[addr];
    else
        return m_cartridge.getVRom()[addr];
}

void MapperNROM::writeCHR(Addr addr, byte value)
{
    if (m_usesCharacterRam)
        m_characterRam[addr] = value;
    else
        std::cout << "Read-only CHR memory write attemp at " << std::hex << addr << std::endl;
}
