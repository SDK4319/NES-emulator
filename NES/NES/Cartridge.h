#pragma once
#include<cstdint>
#include<string>
#include<fstream>
#include<vector>

#include"Mapper_NROM.h"

class Cartridge
{
public:
	Cartridge(const std::string& filepath);
	~Cartridge();

public:
	bool IsVaildImage();

	enum MIRROR {
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;

private:
	bool isValidImage = false;

	uint8_t MapperId = 0;
	uint8_t PRGBanks = 0;
	uint8_t CHRBanks = 0;

	std::vector<uint8_t> PRGMem;
	std::vector<uint8_t> CHRMem;

	std::shared_ptr<Mapper> p_Mapper;

public:
	bool cpuRead(uint16_t addr, uint8_t& data);
	bool cpuWrite(uint16_t addr, uint8_t data);

	bool ppuRead(uint16_t addr, uint8_t& data);
	bool ppuWrite(uint16_t addr, uint8_t data);

	void reset();
};

