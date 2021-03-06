#include"Emulator.h"
#include"Timer.h"
#include"Controller.h"

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0);

	Emulator emu;
	if (emu.create("D:/RETRO/NES/Roms/mario.nes") == false) {
		std::cout << "Emulator Build Failed" << std::endl;
		return 0;
	};

	Timer timer;
	float elapsedTime = timer.getElapsedTime();

	while (true) {
		elapsedTime = timer.getElapsedTime();
		uint8_t controller = getControllerState();
		emu.update(elapsedTime, controller, 0x00);

		cv::Mat src = emu.getRenderedData();
		cv::Mat dst;

		cv::resize(src, dst, cv::Size(256 * 2, 240 * 2), 0, 0, cv::INTER_NEAREST);
		cv::imshow("Render", dst);
		cv::waitKey(1);
	}


	return 0;
}