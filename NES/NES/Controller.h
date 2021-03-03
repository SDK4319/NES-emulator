#pragma once
#include"Rom.h"
#include<opencv2/opencv.hpp>
#include<vector>



class Controller
{
public:
	Controller();
	enum Buttons {
		A,
		B,
		Select,
		Start,
		Up,
		Down,
		Left,
		Right,
		TotalButtons,
	};

	void strobe(byte b);
	byte read();
	void setKeyBindings(const std::vector<char>& keys);

private:
	bool m_strobe;
	unsigned int m_keyStates;

	std::vector<char> m_keyBindings;

};

