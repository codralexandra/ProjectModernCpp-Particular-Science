#include <random>
#include <queue>
#include "game.h"
#include <iostream>
#include <vector>
#include "difficulty.h"
#include <ranges>

Game::Game()
{
}

Game::Game(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }
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

void Game::SetGameID(uint16_t id)
{
	m_gameID = id;
}


std::vector<Player> Game::getPlayers()
{
	return m_players;
}

std::vector<std::string> Game::getWords()
{
	return m_words;
}

uint16_t Game::GetGameID()
{
	return m_gameID;
}


void Game::Start_Game()
{
	std::cout << "Start Game apelata \n";
	int dim_runde = 4;
	//populare vector de cuv in functie de dificultate

	for (int i = 0; i < dim_runde; i++)
	{
		m_round.reset(new Round);
		m_round->StartRound(m_players,m_words);
		
	}
	//stop game
	//clasament
	
	for (auto& player : m_players)
	{
		player.AddGameToGameHistory();
	}
}

Player Game::Winner()
{
	int maxim = 0;
	Player player_max;
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].GetPersonalScore() > maxim) {
			maxim = m_players[i].GetPersonalScore();
			player_max = m_players[i];
		}
	}
	return player_max;

	std::ranges::sort(m_players, [](const Player& a, const Player& b) {
		return a.GetPersonalScore()>b.GetPersonalScore();
		});

	return std::move(m_players[m_players.size() - 1]);

}

