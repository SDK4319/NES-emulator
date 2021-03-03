#include "MainBus.h"

MainBus::MainBus() :
    m_RAM(0x800, 0),
    m_mapper(nullptr)
{
}

byte MainBus::read(Addr addr)
{
    if (addr < 0x2000)
        return m_RAM[addr & 0x7ff];
    else if (addr < 0x4020) {
        if (addr < 0x4000) {
            auto it = m_readCallbacks.find(static_cast<IORegisters>(addr & 0x2007));
            if (it != m_readCallbacks.end())
                return (it->second)();
            //second object is function object ptr
            else
                std::cout << "No read callback registerd for I/O register at: " << std::hex << +addr << std::endl;
        }
        else if (addr < 0x4018 && addr >= 0x4014) { //Only some IO registers
            auto it = m_readCallbacks.find(static_cast<IORegisters>(addr));
            if (it != m_readCallbacks.end())
                return (it->second)();
            else
                std::cout << "No read callback registerd for I/O register at: " << std::hex << +addr << std::endl;
        }
        else
            std::cout << "Read access attempt at: " << std::hex << +addr << std::endl;
    }
    else if (addr < 0x6000) {
        std::cout << "Expansion ROM read attempted/ This is currently unsupported" << std::endl;
    }
    else if (addr < 0x8000) {
        if (m_mapper->hasExtendedRam()) {
            return m_extRAM[addr - 0x6000];
        }
    }
    else {
        return m_mapper->readPRG(addr);
    }
    return 0;
}

void MainBus::write(Addr addr, byte value)
{
    if (addr < 0x2000) {
        m_RAM[addr & 0x7ff] = value;
    }
    else if (addr < 0x4020) {
        if (addr < 0x4000) { //PPU registers, mirrored
            auto it = m_writeCallbacks.find(static_cast<IORegisters>(addr & 0x2007));
            if (it != m_writeCallbacks.end())
                (it->second)(value);
            else
                std::cout << "No write callback registerd for I/O register at: " << std::hex << +addr << std::endl;
        }
        else if (addr < 0x4017 && addr >= 0x4014) { //only same registers 
            auto it = m_writeCallbacks.find(static_cast<IORegisters>(addr));
            if (it != m_writeCallbacks.end())
                (it->second)(value);
            else
                std::cout << "No write callback registered for I/O register at: " << std::hex << +addr << std::endl;
        }
        else {
            std::cout << "Write access attempt at: " << std::hex << +addr << std::endl;
        }
    }
    else if (addr < 0x6000) {
        std::cout << "Expansion ROM access attempted. This is currently unsupported" << std::endl;
    }
    else if (addr < 0x8000) {
        if (m_mapper->hasExtendedRam()) {
            m_extRAM[addr - 0x6000] = value;
        }
    }
    else {
        m_mapper->writePRG(addr, value);
    }
}

byte* MainBus::getPagePtr(byte page)
{
    Addr addr = page << 8;
    if (addr < 0x2000) {
        return &m_RAM[addr & 0x7ff];
    }
    else if (addr < 0x4020) {
        std::cout << "Register address memory pointer access attempt" << std::endl;
    }
    else if (addr < 0x6000) {
        std::cout << "Expansion ROM access attempted, which is unsupported" << std::endl;
    } 
    else if (addr < 0x8000) {
        if (m_mapper->hasExtendedRam()) {
            return &m_extRAM[addr - 0x6000];
        }
    }
    return nullptr;
}

bool MainBus::setMapper(Mapper* mapper)
{
    m_mapper = mapper;

    if (!mapper) {
        std::cout << "Mapper pointer is nullptr" << std::endl;
        return false;
    }

    if (mapper->hasExtendedRam()) {
        m_extRAM.resize(0x2000);
    }

    return true;
}

bool MainBus::setWriteCallback(IORegisters reg, std::function<void(byte)> callback)
{
    if (!callback) {
        std::cout << "callback argument is nullptr " << std::endl;
        return false;
    }
    return m_writeCallbacks.emplace(reg, callback).second;
}

bool MainBus::setReadCallback(IORegisters reg, std::function<byte(void)> callback)
{
    if (!callback) {
        std::cout << "callback argument is nullptr" << std::endl;
        return false;
    }
    return m_readCallbacks.emplace(reg, callback).second;
}
