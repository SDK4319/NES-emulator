#pragma once
#include "MapperInterface.h"

class MapperUxROM : public Mapper
{
public:
	MapperUxROM(Rom& cart);
	void writePRG(Addr addr, byte value);
	byte readPRG(Addr addr);
	byte* getPagePtr(Addr addr);

	byte readCHR(Addr addr);
	void writeCHR(Addr addr, byte value);

private:
	bool m_usesCharacterRam;
	byte* m_lastBankPtr;
	Addr m_selectPRG;
	std::vector<byte> m_characterRam;
};

