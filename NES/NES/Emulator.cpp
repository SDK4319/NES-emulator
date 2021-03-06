#include "Emulator.h"

bool Emulator::create(std::string filepath) {
	cart = std::make_shared<Cartridge>(filepath);

	if (cart->IsVaildImage() == false)
		return false;

	nes.insertCartridge(cart);

	nes.reset();
	isRunning = true;
	return true;
}

bool Emulator::update(float fElapsedTime, uint8_t controller1, uint8_t controller2) {

	/*
	Screen Clear
	*/

	nes.controller[0] = controller1;
	nes.controller[1] = 0x00;

	if (isRunning) {
		if (fResidualTime > 0.0f) {
			fResidualTime -= fElapsedTime;
		}
		else {
			fResidualTime += (1.0f / 60.0f) - fElapsedTime;
			do { nes.clock(); } while (!nes.ppu.frame_complete);
			nes.ppu.frame_complete = false;
		}
	}

	cv::imshow("Pattern Table 0 - Background", nes.ppu.getPatternTable(0, nSelectedPalette));
	cv::imshow("Pattern Table 1 - Foreground", nes.ppu.getPatternTable(1, nSelectedPalette));
	cv::imshow("Render", nes.ppu.getScreen());
	cv::waitKey(1);
	return true;
}