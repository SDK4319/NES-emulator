#include "Header.h"

Bus::Bus()
{
    cpu.setBus(this);
}

Bus::~Bus()
{
}

//address ranges
//0x0000 ~ 0x1FFFF - System RAM Address Range
//0x2000 ~ 0x3FFFF - PPU Address range, mirrored every 8
//0x4014 - dma transfer
//0x4016 ~ 0x4017 - controller

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if (cart->cpuWrite(addr, data)) {

    }
    else if (addr >= 0x0000 && addr <= 0x1FFF) {
        cpuRam[addr & 0x07FF] = data;
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        ppu.cpuWrite(addr & 0x0007, data);
    }
    else if (addr == 0x4014) {
        dma_page = data;
        dma_addr = 0x00;
        dma_transfer = true;
    }
    else if (addr >= 0x4016 && addr <= 0x4017) {
        controller_state[addr & 0x0001] = controller[addr & 0x0001];
    }
}

uint8_t Bus::cpuRead(uint16_t addr, bool isReadOnly)
{
    uint8_t data = 0x00;
    if (cart->cpuRead(addr, data)) {

    } 
    else if (addr >= 0x0000 && addr <= 0x1FFF) {
        data = cpuRam[addr & 0x07FF];
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        data = ppu.cpuRead(addr & 0x0007, isReadOnly);
    }
    else if (addr >= 0x4016 && addr <= 0x4017) {
        data = (controller_state[addr & 0x0001] & 0x80) > 0;
        controller_state[addr & 0x0001] <<= 1;
    }

    return data;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cart)
{
    this->cart = cart;
    ppu.ConnectCartridge(cart);
}

void Bus::reset()
{
    cart->reset();
    cpu.reset();
    ppu.reset();
    nSystemClockCounter = 0;
    dma_page = 0x00;
    dma_addr = 0x00;
    dma_dummy = true;
    dma_transfer = false;
}

void Bus::clock()
{
    ppu.clock();

    if (nSystemClockCounter % 3 == 0) {
        if (dma_transfer) {
            if (dma_dummy) {
                if (nSystemClockCounter % 2 == 1) {
                    dma_dummy = false;
                }
            }
            else {
                //DMA cam take place
                if (nSystemClockCounter % 2 == 0) {
                    dma_data = cpuRead(dma_page << 8 | dma_addr);
                }
                else {
                    ppu.p_OAM[dma_addr] = dma_addr;
                    dma_addr++;
                    
                    if (dma_addr == 0x00) {
                        dma_transfer = false;
                        dma_dummy = true;
                    }
                }
            }
        }
        else {
            cpu.clock();
        }
    }

    if (ppu.nmi) {
        ppu.nmi = false;
        cpu.nmi();

        nSystemClockCounter++;
    }
}
