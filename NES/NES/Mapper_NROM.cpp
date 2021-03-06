#include "Mapper_NROM.h"

Mapper_NROM::Mapper_NROM(uint8_t prgBanks, uint8_t chrBanks) :
    Mapper(prgBanks, chrBanks)
{
}

Mapper_NROM::~Mapper_NROM()
{
}

void Mapper_NROM::reset()
{

}

bool Mapper_NROM::cpuMapRead(uint16_t addr, uint32_t& mapped_addr)
{
    if (0x8000 <= addr && addr <= 0xFFFF) {
        mapped_addr = addr & (PRGBanks > 1 ? 0x7FFF : 0x3FFF);
        return true;
    }
    return false;
}

bool Mapper_NROM::cpuMapWrite(uint16_t addr, uint32_t& mapped_addr, uint8_t data)
{
    if (0x8000 <= addr && addr <= 0xFFFF) {
        mapped_addr = addr & (PRGBanks > 1 ? 0x7FFF : 0x3FFF);
        return true;
    }
    return false;
}

bool Mapper_NROM::ppuMapRead(uint16_t addr, uint32_t& mapped_addr)
{
    if (0x0000 <= addr && addr <= 0x1FFF) {
        mapped_addr = addr;
        return true;
    }
    return false;
}

bool Mapper_NROM::ppuMapWrite(uint16_t addr, uint32_t& mapped_addr)
{
    if (0x0000 <= addr && addr <= 0x1FFF) {
        if (CHRBanks == 0) {
            mapped_addr = addr;
            return true;
        }
    }
    return false;
}

