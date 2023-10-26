#pragma once
#include "User.h"
#include <cstdint>
#include <iostream>
#include <chrono>
class Player: public User 
{
public:


	void SetIsDrawing();
	void UpdateScore(int16_t newscore);
	bool GetIsDrawing();
	int16_t GetPersonalScore();
	std::string GetPlayerUsername();
	bool GetHasTopScore();

private:
	char caracter; //placeholder 
	bool m_isDrawing;
	bool m_hasTopScore;
	int16_t m_personalScore; 
};

