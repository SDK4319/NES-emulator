#pragma once
#include"Mapper.h"

class Mapper_NROM : public Mapper
{
public:
	Mapper_NROM(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper_NROM();

public:
	bool cpuMapRead(uint16_t addr, uint32_t& mapped_addr) override;
	bool cpuMapWrite(uint16_t addr, uint32_t& mapped_addr, uint8_t data = 0) override;
	bool ppuMapRead(uint16_t addr, uint32_t& mapped_addr) override;
	bool ppuMapWrite(uint16_t addr, uint32_t& mapped_addr) override;

	void reset() override;
};

