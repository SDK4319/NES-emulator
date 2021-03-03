#include "Controller.h"
#include<Windows.h>

Controller::Controller() :
	m_keyStates(0),
	m_keyBindings(TotalButtons)
{
}

void Controller::strobe(byte b)
{
	m_strobe = (b & 1);
	if (!m_strobe) {
		m_keyStates = 0;
		int shift = 0;
		for (int button = A; button < TotalButtons; button++) {
			int key = GetAsyncKeyState(m_keyBindings[button]);
			if (key >= 0x8000)
				key |= (1 << shift);
			shift++;
		}
	}
}

byte Controller::read()
{
	byte ret;
	if (m_strobe)
		ret = (GetAsyncKeyState(m_keyBindings[A]) >= 0x8000);
	else {
		ret = (m_keyStates & 1);
		m_keyStates >>= 1;
	}
	return ret | 0x40;
}

void Controller::setKeyBindings(const std::vector<char>& keys)
{
	m_keyBindings = keys;
}
