#pragma once
#include <vector>
#include "Player.h"

class Match
{
public:
private:
	std::vector<Player> m_players;
	static const uint16_t m_rounds = 4;
	std::vector<std::string> m_words;
	std::string m_date; //regex check

};

