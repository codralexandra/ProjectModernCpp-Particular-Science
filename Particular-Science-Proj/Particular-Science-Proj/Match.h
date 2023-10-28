#pragma once
#include <vector>
#include "Player.h"
#include "Difficulty.h"

class Match
{
public:
	Match();
	Match(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date);
private:
	std::vector<Player> m_players;
	Difficulty m_difficulty;
	static const uint16_t m_rounds = 4;
	std::vector<std::string> m_words;
	std::string m_date; //regex check

};

