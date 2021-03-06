#include "Mapper.h"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
	this->PRGBanks = prgBanks;
	this->CHRBanks = chrBanks;

}

Mapper::~Mapper()
{
}
