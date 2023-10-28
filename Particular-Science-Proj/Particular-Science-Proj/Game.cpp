#include "Match.h"

Match::Match()
{
}

Match::Match(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }, m_date{ date }
{
}

void Match::setPlayers(std::vector<Player> players)
{
	m_players = players;
}

void Match::setWords(std::vector<std::string> words)
{
	m_words = words;
}

void Match::setDate(std::string date)
{
	m_date = date;
}

std::vector<Player> Match::getPlayers()
{
	return m_players;
}

std::vector<std::string> Match::getWords()
{
	return m_words;
}

std::string Match::getDate()
{
	return m_date;
}
