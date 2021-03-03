#include "Rom.h"

Rom::Rom() :
	m_nameTableMirroring(0),
	m_mapperNumber(0),
	m_extendedRam(false)
{
}
bool Rom::fileLoad(std::string filepath)
{
	std::ifstream romFile(filepath, std::ios_base::binary | std::ios_base::in);
	if (!romFile) {
		std::cout << "ROM File Open Failed: " << filepath << std::endl;
		return false;
	}

	std::vector<byte> header;
	std::cout << "Reading..." << std::endl;

	//Header
	header.resize(0x10);
	if (!romFile.read(reinterpret_cast<char*>(&header[0]), 0x10)) {
		std::cout << "Reading NES header failed" << std::endl;
		return false;
	}
	if (std::string{ &header[0], &header[4] } != "NES\x1A") {
		std::cout << "Not a vaild NES rom image" << std::endl;
		return false;
	}
	byte banks = header[4];
	std::cout << "16KB PRG-ROM Banks: " << +banks << std::endl;
	if (!banks) {
		std::cout << "ROM has no PRG-ROM banks" << std::endl;
		return false;
	}

	byte vbanks = header[5];
	std::cout << "8KB CHR-ROM Banks: " << +vbanks << std::endl;

	m_nameTableMirroring = header[6] & 0xB;
	std::cout << "Name Table Mirroring: " << +m_nameTableMirroring << std::endl;
	
	m_mapperNumber = ((header[6] >> 4) & 0xf) | (header[7] & 0xf0);
	std::cout << "Mapper #: " << +m_mapperNumber << std::endl;

	m_extendedRam = header[6] & 0x2;
	std::cout << "Extended Ram: " << std::boolalpha << m_extendedRam << std::endl;

	if (header[6] & 0x4) {
		std::cout << "Trainer is not supported." << std::endl;
		return false;
	}

	if ((header[0xA] & 0x3) == 0x2 || (header[0xA] & 0x1)) {
		std::cout << "PAL Rom not supported." << std::endl;
		return false;
	}
	else {
		std::cout << "Rom is NTSC compatible." << std::endl;
	}

	//PRG-ROM 16KB banks
	unsigned int PRG_rom_size = 0x4000 * banks;
	m_PRG_ROM.resize(PRG_rom_size);
	if (!romFile.read(reinterpret_cast<char*>(&m_PRG_ROM[0]), PRG_rom_size)) {
		std::cout << "Reading PRG-ROM from image file failed." << std::endl;
		return false;
	}

	//CHR-ROM 8KB banks
	if (vbanks) {
		unsigned int CHR_rom_size = 0x2000 * vbanks;
		m_CHR_ROM.resize(CHR_rom_size);
		if (!romFile.read(reinterpret_cast<char*>(&m_CHR_ROM[0]), CHR_rom_size)) {
			std::cout << "Reading CHR-ROM from image file failed" << std::_Unlock_shared_ptr_spin_lock;
			return false;
		}
	}
	else {
		std::cout << "Cartridge with CHR-RAM" << std::endl;
	}
	return true;
}
std::vector<byte>& Rom::getRom()
{
	return m_PRG_ROM;
}
std::vector<byte>& Rom::getVRom()
{
	return m_CHR_ROM;
}
byte Rom::getMapper()
{
	return m_mapperNumber;
}
byte Rom::getNameTableMirroring()
{
	return m_nameTableMirroring;
}
bool Rom::hasExtendedRam()
{
	return m_extendedRam;
}
