#pragma once
import user;
#include <cstdint>
#include <chrono>
#include <iostream>


 class Player : public Scribble::User
	{
	public:
		//constructors and destructor
		Player();
		Player(bool& isDrawing);
		Player(const Player& player);
		//Player(Player&& other);
		Player(bool& hasGuessed, uint16_t& timeGuessed,
			bool& isDrawer, uint16_t& personalScore, const std::string& email, const std::string& password,
			uint16_t& personalBest);
		~Player() = default;

		//setter
		void SetIsDrawer(bool isDrawing);
		//void SetIsDrawer(bool&& isDrawing);
		void SetHasGuessed(bool hasGuessed);
		void SetScore(const uint16_t& newscore);

		//getter
		bool GetIsDrawer() const;
		uint16_t GetPersonalScore() const;
		bool GetHasGuessed() const;
		uint16_t GetTimeGuessed() const;
		
		//operators
		Player& operator = (const Player& player);
		//Player& operator=(Player&& other)noexcept;
		bool operator<(const Player& player) const;
		bool operator>(const Player& player) const;


	private:
		bool m_hasGuessed; //pt calculare scor
		uint16_t m_timeGuessed; //pt calculare scor
		bool m_isDrawer; // rol
		uint16_t m_personalScore; //ca sa tinem minte scorul

	};
 // std::ostream& operator<<(std::ostream& os, Player& player);
