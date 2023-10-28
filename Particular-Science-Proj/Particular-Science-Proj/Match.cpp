#include "Match.h"

Match::Match()
{
}

Match::Match(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }, m_date{ date }
{
}
