#include "MapperUxROM.h"

MapperUxROM::MapperUxROM(Rom& cart) :
    Mapper(cart, Mapper::UxROM),
    m_selectPRG(0)
{
    if (cart.getVRom().size() == 0) {
        m_usesCharacterRam = true;
        m_characterRam.resize(0x2000);
        std::cout << "Uses character RAM" << std::endl;
    }
    else
        m_usesCharacterRam = false;

    m_lastBankPtr = &cart.getRom()[cart.getRom().size() - 0x4000];
}

void MapperUxROM::writePRG(Addr addr, byte value)
{
    m_selectPRG = value;
}

byte MapperUxROM::readPRG(Addr addr)
{
    if (addr < 0xc000)
        return m_cartridge.getRom()[((addr - 0x8000) & 0x3fff) | (m_selectPRG << 14)];
    else
        return *(m_lastBankPtr + (addr & 0x3fff));
}

byte* MapperUxROM::getPagePtr(Addr addr)
{
    if (addr < 0xc000)
        return &m_cartridge.getRom()[((addr - 0x8000) & 0x3fff) | (m_selectPRG << 14)];
    else
        return m_lastBankPtr + (addr & 0x3fff);
}

byte MapperUxROM::readCHR(Addr addr)
{
    if (m_usesCharacterRam)
        return m_characterRam[addr];
    else
        return m_cartridge.getVRom()[addr];
}

void MapperUxROM::writeCHR(Addr addr, byte value)
{
    if (m_usesCharacterRam)
        m_characterRam[addr] = value;
    else
        std::cout << "Read-only CHR memory write attempt at " << std::hex << addr << std::endl;
}
