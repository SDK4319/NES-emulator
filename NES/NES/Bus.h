#pragma once
#include"Header.h"


class Bus
{
public:
	Bus();
	~Bus();
	void write(ui16 addr, ui8 data);

public:
	CPU cpu;
	std::array<ui8, 64 * 1024> ram;

public:
	void write(ui16 addr, ui8 data);
	ui8 read(ui16 addr, bool isReadOnly = false);
};

