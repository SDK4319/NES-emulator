#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using byte = std::uint8_t;
using Addr = std::uint16_t;

class Rom
{
public:
	Rom();
	bool fileLoad(std::string filepath);
	std::vector<byte>& getRom();
	std::vector<byte>& getVRom();
	byte getMapper();
	byte getNameTableMirroring();
	bool hasExtendedRam();

private:
	std::vector<byte> m_PRG_ROM;
	std::vector<byte> m_CHR_ROM;
	byte m_nameTableMirroring;
	byte m_mapperNumber;
	bool m_extendedRam;
	bool m_chrRam;
};

