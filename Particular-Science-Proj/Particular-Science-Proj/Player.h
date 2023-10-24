#pragma once
#include <cstdint>
#include <iostream>
#include <chrono>
class Player
{
public:


	bool GetIsDrawing();
	int16_t GetPersonalScore();
	void UpdateScore();

private:
	//caracter
	bool m_isDrawing;
	bool m_isLeader;
	int16_t m_personalScore;
	//std::chrono::time_point<std::chrono::high_resolution_clock>startTime;

};

