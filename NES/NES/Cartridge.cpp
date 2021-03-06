#include "Header.h"

Cartridge::Cartridge(const std::string& filepath)
{
    struct Header {
        char name[4];
        uint8_t prg_rom_chunks;
        uint8_t chr_rom_chunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prg_ram_size;
        uint8_t tv_system1;
        uint8_t tv_system2;
        char none[5];
    } header;

    isValidImage = false;

    std::ifstream ifs;
    ifs.open(filepath, std::ifstream::binary);
    if (ifs.is_open()) {
        ifs.read((char*)&header, sizeof(Header));

        if (header.mapper1 & 0x04)
            ifs.seekg(512, std::ios_base::cur);

        this->MapperId = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
        this->mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

        uint8_t file_type = 1;

        if (file_type == 1) {
            this->PRGBanks = header.prg_rom_chunks;
            this->PRGMem.resize(PRGBanks * 16384);
            ifs.read((char*)PRGMem.data(), PRGMem.size());

            this->CHRBanks = header.chr_rom_chunks;
            if (this->CHRBanks == 0) {
                this->CHRMem.resize(8192);
            }
            else {
                this->CHRMem.resize(this->CHRBanks * 8192);
            }
            ifs.read((char*)CHRMem.data(), CHRMem.size());
        }

        if (this->MapperId == 0) {
            p_Mapper = std::make_shared<Mapper_NROM>(this->PRGBanks, this->CHRBanks); 
            this->isValidImage = true;
        }
        else {
            std::cout << "MapperID: " << this->MapperId << " is unsupported yet";
            this->isValidImage = false;
        }

        ifs.close();
    }
}

Cartridge::~Cartridge()
{
}

bool Cartridge::IsVaildImage()
{
    return this->isValidImage;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t& data)
{
    uint32_t mapped_addr = 0;
    if (this->p_Mapper->cpuMapRead(addr, mapped_addr)) {
        data = this->PRGMem[mapped_addr];
        return true;
    }
    return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (this->p_Mapper->cpuMapWrite(addr, mapped_addr, data)) {
        this->PRGMem[mapped_addr] = data;
        return true;
    }
    return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t& data)
{
    uint32_t mapped_addr = 0;
    if (this->p_Mapper->ppuMapRead(addr, mapped_addr)) {
        data = this->CHRMem[mapped_addr];
        return true;
    }
    return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (this->p_Mapper->ppuMapWrite(addr, mapped_addr)) {
        this->CHRMem[mapped_addr] = data;
        return true;
    }
    return false;
}

void Cartridge::reset()
{
    if (this->p_Mapper != nullptr)
        this->p_Mapper->reset();
}
