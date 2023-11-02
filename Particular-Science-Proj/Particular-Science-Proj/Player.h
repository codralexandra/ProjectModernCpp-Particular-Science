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


	void SetNickname(std::string nickname);
	void SetIsDrawing(bool isDrawing);
	void UpdateScore(int16_t newscore);
	void UpdatePosition(uint16_t position);


	std::string GetNickname();
	bool GetIsDrawing();
	int16_t GetPersonalScore();
	bool GetHasTopScore();
	uint16_t GetPosition();



	Player& operator = (const Player& player);
	bool operator<(const Player& player) const;
	bool operator>(const Player& player) const;

private:
	std::string m_nickname;
	bool m_isDrawing;
	bool m_hasTopScore;
	int16_t m_personalScore; 
	uint16_t m_position;
};

