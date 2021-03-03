#include "MapperSxROM.h"

MapperSxROM::MapperSxROM(Rom& cart, std::function<void(void)> mirroring_cb) :
	Mapper(cart, Mapper::SxROM),
	m_mirroringCallback(mirroring_cb),
	m_mirroring(Horizontal),
	m_modeCHR(0),
	m_modePRG(3),
	m_tempRegister(0),
	m_writeCounter(0),
	m_regPRG(0),
	m_regCHR0(0),
	m_regCHR1(0),
	m_firstBankPRG(nullptr),
	m_secondBankPRG(nullptr),
	m_firstBankCHR(nullptr),
	m_secondBankCHR(nullptr)
{
	if (cart.getVRom().size() == 0) {
		m_usesCharacterRam = true;
		m_characterRam.resize(0x2000);
		std::cout << "Uses Character RAM" << std::endl;
	}
	else {
		std::cout << "Using CHR-ROM" << std::endl;
		m_usesCharacterRam = false;
		m_firstBankCHR = &cart.getVRom()[0];
		m_secondBankCHR = &cart.getVRom()[(byte)0x1000 * m_regCHR1];
	}

	m_firstBankPRG = &cart.getRom()[0];
	m_secondBankPRG = &cart.getRom()[cart.getRom().size() - 0x4000];
}

NameTableMirroring MapperSxROM::getNameTableMirroring()
{
	return m_mirroring;
}

void MapperSxROM::writePRG(Addr addr, byte value)
{
	if (!(value & 0x80)) {
		m_tempRegister = (m_tempRegister >> 1) | ((value & 1) << 4);
		++m_writeCounter;

		if (m_writeCounter == 5) {
			if (addr <= 0x9fff) {
				switch (m_tempRegister & 0x3) {
					case 0: m_mirroring = OneScreenLower; break;
					case 1: m_mirroring = OneScreenHigher; break;
					case 2: m_mirroring = Vertical; break;
					case 3: m_mirroring = Horizontal; break;
				}
				m_mirroringCallback();

				m_modeCHR = (m_tempRegister & 0x10) >> 4;
				m_modePRG = (m_tempRegister & 0xc) >> 2;
				calculatePRGPointers();

				//Recalculate CHR pointers
				if (m_modeCHR == 0) {
					m_firstBankCHR = &m_cartridge.getVRom()[(byte)0x1000 * (m_regCHR0 | 1)];
					m_secondBankCHR = m_firstBankCHR + 0x1000;
				}
				else { //two 4KB banks
					m_firstBankCHR = &m_cartridge.getVRom()[(byte)0x1000 * m_regCHR0];
					m_secondBankCHR = &m_cartridge.getVRom()[(byte)0x1000 * m_regCHR1];
				}
			}
			else if (addr <= 0xbfff) {
				m_regCHR0 = m_tempRegister;
				//or 1 if 8KB mode
				m_firstBankCHR = &m_cartridge.getVRom()[(byte)0x1000 * (m_tempRegister | (1 - m_modeCHR))];
				if (m_modeCHR == 0)
					m_secondBankCHR = m_firstBankCHR + 0x1000;
			}
			else if (addr <= 0xdfff) {
				m_regCHR1 = m_tempRegister;
				if (m_modeCHR == 1)
					m_secondBankCHR = &m_cartridge.getVRom()[(byte)0x1000 * m_tempRegister];
			}
			else {
				//TODO PRG-RAM
				if ((m_tempRegister & 0x10) == 0x10) {
					std::cout << "PRG-RAM activated" << std::endl;
				}

				m_tempRegister &= 0xf;
				m_regPRG = m_tempRegister;
				calculatePRGPointers();
			}

			m_tempRegister = 0;
			m_writeCounter = 0;
		}
	}
	else {
		m_tempRegister = 0;
		m_writeCounter = 0;
		m_modePRG = 3;
		calculatePRGPointers();
	}
}

void MapperSxROM::calculatePRGPointers()
{
	if (m_modePRG <= 1) { // 32KB changeable
		//equivalent to multiplying 0x8000 * (m_regPRG >> 1)
		m_firstBankPRG = &m_cartridge.getRom()[0x4000 * (m_regPRG & ~1)];
		m_secondBankPRG = m_firstBankPRG + 0x4000; //add 16kb
	}
	else if (m_modePRG == 2) { // fix first switch second
		m_firstBankPRG = &m_cartridge.getRom()[0];
		m_secondBankPRG = m_firstBankPRG + 0x4000 * m_regPRG;
	}
	else { // switch first fix second
		m_firstBankPRG = &m_cartridge.getRom()[0x4000 * m_regPRG];
		m_secondBankPRG = &m_cartridge.getRom()[m_cartridge.getRom().size() - 0x4000];
	}
}

byte MapperSxROM::readPRG(Addr addr)
{
	if (addr < 0xc000)
		return *(m_firstBankPRG + (addr & 0x3fff));
	else
		return *(m_secondBankPRG + (addr & 0x3fff));
}

byte* MapperSxROM::getPagePtr(Addr addr)
{
	if (addr < 0xc000)
		return (m_firstBankPRG + (addr & 0x3fff));
	else
		return (m_secondBankPRG + (addr & 0x3fff));
}

byte MapperSxROM::readCHR(Addr addr)
{
	if (m_usesCharacterRam)
		return m_characterRam[addr];
	else if (addr < 0x1000)
		return *(m_firstBankCHR + addr);
	else
		return *(m_secondBankCHR + (addr & 0xfff));
}

void MapperSxROM::writeCHR(Addr addr, byte value)
{
	if (m_usesCharacterRam)
		m_characterRam[addr] = value;
	else
		std::cout << "Read-only CHR memory write attempt at " << std::hex << addr << std::endl;
}


