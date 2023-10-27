#pragma once
#include <cstdint>
#include <string>
class Score
{
private:
	uint16_t m_timp;
	std::string m_dificultate;

public:
	Score();

	Score(uint16_t timp, const std::string& dificultate);
	
	Score(const Score& s);
	
	Score& operator=(const Score& s);
	
	void SetTime(uint16_t timp);
	
	void SetDificulty(const std::string& dificultate);
	
	uint16_t GetTime();

	std::string GetDificulty();
	
};

