#pragma once
import user;
#include <cstdint>
#include <chrono>
#include <iostream>


 class Player : public Scribble::User
	{
	public:

		Player();
		Player(bool isDrawing);
		Player(const Player& player);

		Player(bool hasGuessed, uint16_t timeGuessed,
			bool isDrawer, int16_t personalScore, const std::string& email, const std::string& password,
			uint16_t personalBest);

		void SetIsDrawer(bool isDrawing);
		void SetHasGuessed(bool hasGuessed);
		void SetScore(int16_t newscore);

		bool GetIsDrawer() const;
		int16_t GetPersonalScore() const;
		bool GetHasGuessed() const;
		uint16_t GetTimeGuessed() const;
		

		Player& operator = (const Player& player);
		bool operator<(const Player& player) const;
		bool operator>(const Player& player) const;

	private:
		bool m_hasGuessed; //pt calculare scor
		uint16_t m_timeGuessed; //pt calculare scor
		bool m_isDrawer; // rol
		int16_t m_personalScore; //ca sa tinem minte scorul

	};
 // std::ostream& operator<<(std::ostream& os, Player& player);
