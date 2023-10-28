#include "Game.h"

Game::Game()
{
}

Game::Game(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }, m_date{ date }
{
}

void Game::setPlayers(std::vector<Player> players)
{
	m_players = players;
}

void Game::setWords(std::vector<std::string> words)
{
	m_words = words;
}

void Game::setDate(std::string date)
{
	m_date = date;
}

std::vector<Player> Game::getPlayers()
{
	return m_players;
}

std::vector<std::string> Game::getWords()
{
	return m_words;
}

std::string Game::getDate()
{
	return m_date;
}
