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

Game::Game(std::vector<Player> players, Difficulty difficulty, std::vector<Word> words, std::string date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }
{
}

void Game::setPlayers(const std::vector<Player>& players)
{
	m_players = players;
}

void Game::setWords(const std::vector<Word>& words)
{
	m_words = words;
}

void Game::SetGameID(const uint16_t& id)
{
	m_gameID = id;
}

void Game::AddPlayer(const Player& p)
{
	m_players.push_back(p);
}

void Game::SetDifficulty(const Difficulty& difficulty)
{
	m_difficulty = difficulty;
}

void Game::SetLobbyState(const LobbyState& lobbystate)
{
	m_lobbyState = lobbystate;
}


std::vector<Player> Game::getPlayers() const
{
	return m_players;
}

std::vector<Word> Game::getWords() const
{
	return m_words;
}

uint16_t Game::GetGameID() const
{
	return m_gameID;
}

Difficulty Game::GetDifficulty() const
{
	return m_difficulty;
}


void Game::Start_Game(crow::SimpleApp& m_app)
{
	CROW_ROUTE(m_app, "/game/startgame")
		.methods("GET"_method)
		([this]() {

		return crow::response(200, "The game has started");
			});
	std::cout << "Start Game apelata \n";
	int dim_runde = 4;
	//populare vector de cuv in functie de dificultate

	for (int i = 0; i < dim_runde; i++)
	{
		m_round.reset(new Round);
		m_round->StartRound(m_players, m_words);

	}
	//stop game
	//clasament

	for (int i = 0; i < m_players.size(); i++)
	{

	//player.AddGameToGameHistory();
	}
}

LobbyState Game::GetLobbyState()
{
	return m_lobbyState;
}



Player Game::Winner()
{
	/*int maxim = 0;
	Player player_max;
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].GetPersonalScore() > maxim) {
			maxim = m_players[i].GetPersonalScore();
			player_max = m_players[i];
		}
	}
	return player_max;*/

	std::ranges::sort(m_players, [](const Player& a, const Player& b) {
		return a.GetPersonalScore() > b.GetPersonalScore();
		});

	return std::move(m_players[m_players.size() - 1]);

}

