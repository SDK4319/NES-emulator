#pragma once
#include "MapperInterface.h"

class MapperSxROM : public Mapper
{
public:
	MapperSxROM(Rom& cart, std::function<void(void)> mirroring_cb);
	void writePRG(Addr addr, byte value);
	byte readPRG(Addr addr);
	byte* getPagePtr(Addr addr);

	byte readCHR(Addr addr);
	void writeCHR(Addr addr, byte value);

	NameTableMirroring getNameTableMirroring();

private:
	void calculatePRGPointers();

	std::function<void(void)> m_mirroringCallback;
	NameTableMirroring m_mirroring;

	bool m_usesCharacterRam;
	int m_modeCHR;
	int m_modePRG;

	byte m_tempRegister;
	int m_writeCounter;

	byte m_regPRG;
	byte m_regCHR0;
	byte m_regCHR1;

	byte* m_firstBankPRG;
	byte* m_secondBankPRG;

	byte* m_firstBankCHR;
	byte* m_secondBankCHR;

	std::vector<byte> m_characterRam;
};

