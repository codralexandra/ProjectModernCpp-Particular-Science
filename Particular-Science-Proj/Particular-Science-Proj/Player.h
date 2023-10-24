#pragma once
#include <cstdint>
#include <iostream>
#include <chrono>
class Player
{
public:

private:
	//caracter
	bool isDrawing;
	bool isLeader;
	int16_t personalScore;
	std::chrono::time_point<std::chrono::high_resolution_clock>startTime;

};

