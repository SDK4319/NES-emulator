#pragma once
#include<Windows.h>
#include<cstdint>

uint8_t getControllerState() {
	uint8_t state = 0x00;
	state |= (GetAsyncKeyState(0x4B)) ? 0x80 : 0x00;	//A
	state |= (GetAsyncKeyState(0x4A)) ? 0x40 : 0x00;	//B
	state |= (GetAsyncKeyState(0x5A)) ? 0x20 : 0x00;	//Select
	state |= (GetAsyncKeyState(0x58)) ? 0x10 : 0x00;	//Start
	state |= (GetAsyncKeyState(0x57)) ? 0x08 : 0x00;	//UP
	state |= (GetAsyncKeyState(0x53)) ? 0x04 : 0x00;	//DOWN
	state |= (GetAsyncKeyState(0x41)) ? 0x02 : 0x00;	//LEFT
	state |= (GetAsyncKeyState(0x44)) ? 0x01 : 0x00;	//RIGHT

	return state;
}