#pragma once
#include<chrono>

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