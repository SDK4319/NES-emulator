#include "Emulator.h"

#include<thread>
#include<chrono>

Emulator::Emulator() :
	m_cpu(m_bus),
	m_ppu(m_pictureBus, m_emulatorScreen),
	m_screenScale(2.f),
	m_cycleTimer(),
	m_cpuCycleDuration(std::chrono::nanoseconds(559))
{
	if (!m_bus.setReadCallback(PPUSTATUS, [&](void) {return m_ppu.getStatus(); }) ||
		!m_bus.setReadCallback(PPUDATA, [&](void) {return m_ppu.getData(); }) ||
		!m_bus.setReadCallback(JOY1, [&](void) {return m_controller1.read(); }) ||
		!m_bus.setReadCallback(JOY2, [&](void) {return m_controller2.read(); }) ||
		!m_bus.setReadCallback(OAMDATA, [&](void) {return m_ppu.getOAMData(); })) {
		std::cout << "Failed to set I/O callbacks" << std::endl;
	}

	if (!m_bus.setWriteCallback(PPUCTRL, [&](byte b) {m_ppu.control(b); }) ||
		!m_bus.setWriteCallback(PPUMASK, [&](byte b) {m_ppu.setMask(b); }) ||
		!m_bus.setWriteCallback(OAMADDR, [&](byte b) {m_ppu.setOAMAddress(b); }) ||
		!m_bus.setWriteCallback(PPUADDR, [&](byte b) {m_ppu.setDataAddress(b); }) ||
		!m_bus.setWriteCallback(PPUSCROL, [&](byte b) {m_ppu.setScroll(b); }) ||
		!m_bus.setWriteCallback(PPUDATA, [&](byte b) {m_ppu.setData(b); }) ||
		!m_bus.setWriteCallback(OAMDMA, [&](byte b) {DMA(b); }) ||
		!m_bus.setWriteCallback(JOY1, [&](byte b) {m_controller1.strobe(b); m_controller2.strobe(b); })||
		!m_bus.setWriteCallback(OAMDATA, [&](byte b) {m_ppu.setOAMData(b); })
		) {
		std::cout << "Failed to set I/O callbacks" << std::endl;
	}
	m_ppu.setInterruptCallback([&]() {m_cpu.interrupt(CPU::NMI); });
}

void Emulator::run(std::string rom_path)
{
	if (!m_cartridge.fileLoad(rom_path))
		return;

	m_mapper = Mapper::create(static_cast<Mapper::Type>(m_cartridge.getMapper()),
		m_cartridge, [&]() {m_pictureBus.updateMirroring(); });

	if (!m_mapper) {
		std::cout << "Creating Mapper failed. Probably unsupported." << std::endl;
		return;
	}

	if (!m_bus.setMapper(m_mapper.get()) ||
		!m_pictureBus.setMapper(m_mapper.get()))
		return;

	m_cpu.reset();
	m_ppu.reset();

	m_emulatorScreen.create(NESVideoWidth, NESVideoHeight, cv::Scalar(255, 255, 255));

	m_cycleTimer = std::chrono::high_resolution_clock::now();
	m_elapsedTime = m_cycleTimer - m_cycleTimer;

	bool pause = false;
	
	while (true) {
		char key = cv::waitKey(1);
		switch (key) {
		case ' ':
			pause = !pause;
			if (!pause)
				m_cycleTimer = std::chrono::high_resolution_clock::now();
		case 27:
			break;
		}

		if (!pause) {
			m_elapsedTime += std::chrono::high_resolution_clock::now() - m_cycleTimer;

			//while (m_elapsedTime > m_cpuCycleDuration) {
				m_ppu.step();
				m_ppu.step();
 				m_ppu.step();
				m_cpu.step();
			//	m_elapsedTime -= m_cpuCycleDuration;
			//}
			//RenderFrame = m_emulatorScreen.getFrame(800, 600);
			m_emulatorScreen.disp();
			//cv::imshow("Render", RenderFrame);
			cv::waitKey(1);
			//m_cycleTimer = std::chrono::high_resolution_clock::now();
		}
		else {
			cv::waitKey(1000 / 60);
		}
	}

}

void Emulator::DMA(byte page)
{
	m_cpu.skipDMACycles();
	auto page_ptr = m_bus.getPagePtr(page);
	m_ppu.doDMA(page_ptr);
}

void Emulator::setVideoWidth(int width)
{
	m_screenScale = width / float(NESVideoWidth);
}

void Emulator::setVideoHeight(int height)
{
	m_screenScale = height / float(NESVideoHeight);
}

void Emulator::setVideoScale(float scale)
{
	m_screenScale = scale;
}

void Emulator::setKeys(std::vector<char>& p1, std::vector<char>& p2)
{
	m_controller1.setKeyBindings(p1);
	m_controller2.setKeyBindings(p2);
}
