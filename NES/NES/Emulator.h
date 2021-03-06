#pragma once

#include<iostream>
#include<sstream>
#include<chrono>

#include"Bus.h"
#include"CPU.h"

class Emulator
{
public:
	Emulator() {};
	~Emulator() {};

private:
	Bus nes;
	std::shared_ptr<Cartridge> cart;
	bool isRunning = false;
	float fResidualTime = 0.0f;

	uint8_t nSelectedPalette = 0x00;

public:

	bool create(std::string filepath);
	bool update(float fElapsedTime, uint8_t controller1, uint8_t controller2 = 0x00);
	cv::Mat getRenderedData() { return nes.ppu.GetScreen(); }
};

