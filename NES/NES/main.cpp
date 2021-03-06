#include"Emulator.h"

int main() {
	Emulator emu;
	if (emu.create("D:/RETRO/NES/Roms/mario.nes") == false) {
		std::cout << "Emulator Build Failed" << std::endl;
		return 0;
	};
	
	Timer timer;


	while (true) {
		float elapsedTime = timer.getElapsedTime();
		emu.update(elapsedTime, 0x00, 0x00);
	}


	return 0;
}