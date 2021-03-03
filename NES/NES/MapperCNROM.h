#pragma once
#include"MapperInterface.h"

class MapperCNROM : public Mapper
{
public:
	MapperCNROM(Rom& cart);
	void writePRG(Addr addr, byte value);
	byte readPRG(Addr addr);
	byte* getPagePtr(Addr addr);

	byte readCHR(Addr addr);
	void writeCHR(Addr addr, byte value);

private:
	bool m_oneBank;
	Addr m_selectCHR;
};

