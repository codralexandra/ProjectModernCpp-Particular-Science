#pragma once
#include "User.h"
#include <cstdint>
#include <iostream>
#include <chrono>
class Player: public User 
{
public:
	
	Player();
	Player(bool isDrawing);
	Player(const Player& player);

	void SetIsDrawing();
	void UpdateScore(int16_t newscore);
	void UpdatePosition(uint16_t position);


	bool GetIsDrawing();
	int16_t GetPersonalScore();
	bool GetHasTopScore();
	uint16_t GetPosition();




private:
	bool m_isDrawing;
	bool m_hasTopScore;
	int16_t m_personalScore; 
	uint16_t m_position;
};

