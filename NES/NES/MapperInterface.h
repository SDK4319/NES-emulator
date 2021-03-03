#pragma once

#include"Rom.h"
#include<memory>
#include<functional>

enum NameTableMirroring {
	Horizontal = 0,
	Vertical = 1,
	FourScreen = 8,
	OneScreenLower,
	OneScreenHigher,
};

class Mapper {
public:
	enum Type {
		NROM = 0,
		SxROM,
		UxROM,
		CNROM
	};

	Mapper(Rom& cart, Type t) : m_cartridge(cart), m_type(t) {}
	virtual void writePRG(Addr addr, byte value) = 0;
	virtual byte readPRG(Addr addr) = 0;
	virtual byte* getPagePtr(Addr addr) = 0;

	virtual byte readCHR(Addr addr) = 0;
	virtual void writeCHR(Addr addr, byte value) = 0;

	virtual NameTableMirroring getNameTableMirroring();

	bool inline hasExtendedRam() {
		return m_cartridge.hasExtendedRam();
	}

	static std::unique_ptr<Mapper> create(Type mapper_type, Rom& cart,
		std::function<void(void)> mirroring_cb);

protected:
	Rom& m_cartridge;
	Type m_type;
};