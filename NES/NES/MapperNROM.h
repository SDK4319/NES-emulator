#pragma once
#include "MapperInterface.h"

class MapperNROM : public Mapper
{
public:
	MapperNROM(Rom& cart);
	void writePRG(Addr addr, byte value);
	byte readPRG(Addr addr);
	byte* getPagePtr(Addr addr);

	byte readCHR(Addr addr);
	void writeCHR(Addr addr, byte value);

private:
	bool m_oneBank;
	bool m_usesCharacterRam;

	std::vector<byte> m_characterRam;
};

