#include "Bus.h"

Bus::Bus()
{
    cpu.setBus(this);

    //ram clear
    for (auto& i : ram) i = 0x00;
}

Bus::~Bus()
{
}

void Bus::write(ui16 addr, ui8 data)
{
    if (0x0000 <= addr && addr <= ram_max)
        ram[addr] = data;
}

ui8 Bus::read(ui16 addr, bool isReadOnly)
{
    if (0x0000 <= addr && addr <= ram_max)
       return ram[addr];

    return 0x00;
}
