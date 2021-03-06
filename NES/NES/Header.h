#pragma once
#include<iostream>
#include<vector>
#include<array>
#include<string>
#include<map>
#include<fstream>
#include<string>
#include<sstream>
#include<chrono>
#include<opencv2/opencv.hpp>

#include"Bus.h"
#include"CPU.h"
#include"PPU.h"
#include"Mapper.h"
#include"Mapper_NROM.h"
#include"Cartridge.h"

using uint32_t = uint32_t;
using uint16_t = uint16_t;
using uint8_t = uint8_t;
using int32_t = int32_t;
using int16_t = int16_t;
using i8 = int8_t;

const auto cpu_ram_max = 0x1FFF;

class Timer {

public:
	Timer() {
		start = std::chrono::system_clock::now();
		end = std::chrono::system_clock::now();
	}
	float getElapsedTime() {
		end = std::chrono::system_clock::now();
		std::chrono::duration<float> sec = end - start;
		start = std::chrono::system_clock::now();
		return sec.count();
	}

public:
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

};
