#pragma once

#include<vector>
#include"Rom.h"
#include"MapperInterface.h"

class PictureBus
{
public:
	PictureBus();
	byte read(Addr addr);
	void write(Addr addr, byte value);

	bool setMapper(Mapper* mapper);
	byte readPalette(byte paletteAddr);

	void updateMirroring();

private:
	std::vector<byte> m_RAM;
	std::size_t NameTable0, NameTable1, NameTable2, NameTable3;
	//indices where they start in RAM vector

	std::vector<byte> m_palette;
	Mapper* m_mapper;
};

