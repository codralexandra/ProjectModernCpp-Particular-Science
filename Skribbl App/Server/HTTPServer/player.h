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
		Player(bool& hasGuessed, double& timeGuessed,
			bool& isDrawer, uint16_t& personalScore, const std::string& email, const std::string& password,
			uint16_t& personalBest);
		~Player() = default;

		//setter
		void SetIsDrawer(bool isDrawing);
		void SetTimeGuessed(double time);
		void SetHasGuessed(bool hasGuessed);
		void SetScore(const double& newscore);
		void SetHasReceivedPixels(bool received);

		//getter
		bool GetIsDrawer() const;
		double GetPersonalScore() const;
		bool GetHasGuessed() const;
		double GetTimeGuessed() const;
		bool GetHasReceivedPixels() const;

		
		//operators
		Player& operator = (const Player& player);
		//Player& operator=(Player&& other)noexcept;
		bool operator<(const Player& player) const;
		bool operator>(const Player& player) const;


	private:
		bool m_hasGuessed; //pt calculare scor
		double m_timeGuessed; //pt calculare scor
		bool m_isDrawer; // rol
		double m_personalScore; //ca sa tinem minte scorul
		bool m_hasReceivedPixels;

	};
 // std::ostream& operator<<(std::ostream& os, Player& player);
