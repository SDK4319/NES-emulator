#include"Emulator.h"

/*
A B Select Start Up Down Left Right
*/

int main() {
	std::vector<char> p1({ 'j','k','z','x','w','s','a','d','.','.' });
	std::vector<char> p2({ '.','.','.','.','.','.','.','.','.','.' });
	Emulator emulator;

	std::string filepath = "D:\\RETRO\\NES\\Roms\\Ninja Gaiden (USA).nes";
	emulator.setKeys(p1, p2);
	emulator.run(filepath);
	return 0;
}