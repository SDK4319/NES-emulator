#pragma once
#include<opencv2/opencv.hpp>
#include<chrono>

#include "CPU.h"
#include "PPU.h"
#include "MainBus.h"
#include "PictureBus.h"
#include "Controller.h"

using TimePoint = std::chrono::high_resolution_clock::time_point;

const int NESVideoWidth = ScanlineVisibleDots;
const int NESVideoHeight = VisibleScanlines;

class Emulator
{
public:
	Emulator();
	void run(std::string rom_path);
	void setVideoWidth(int width);
	void setVideoHeight(int height);
	void setVideoScale(float scale);
	void setKeys(std::vector<char>& p1, std::vector<char>& p2);

private:
	void DMA(byte page);

	MainBus m_bus;
	PictureBus m_pictureBus;
	CPU m_cpu;
	PPU m_ppu;
	Rom m_cartridge;
	std::unique_ptr<Mapper> m_mapper;
	
	Controller m_controller1, m_controller2;

	cv::Mat RenderFrame;
	VScreen m_emulatorScreen;
	float m_screenScale;

	TimePoint m_cycleTimer;

	std::chrono::high_resolution_clock::duration m_elapsedTime;
	std::chrono::nanoseconds m_cpuCycleDuration;

};

