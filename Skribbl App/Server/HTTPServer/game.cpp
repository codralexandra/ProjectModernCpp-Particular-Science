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

Game::Game(std::unordered_map<std::string, Player> players, Difficulty difficulty, std::vector<Word> words, std::string date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }
{
}

void Game::setPlayers(const std::unordered_map<std::string,Player>& players)
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
	m_players[p.GetUsername()] = p;
}

void Game::SetDifficulty(const Difficulty& difficulty)
{
	m_difficulty = difficulty;
}

void Game::SetLobbyState(const LobbyState& lobbystate)
{
	m_lobbyState = lobbystate;
}


std::unordered_map<std::string, Player> Game::getPlayers() const
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
	int dim_runde = 4;
	//populare vector de cuv in functie de dificultate

	for (int i = 0; i < dim_runde; i++)
	{
		m_round.reset(new Round);
		m_round->StartRound(m_players, m_words, m_app);

	}
	//stop game
	//clasament

	for (const auto& it : m_players)
	{

		crow::json::wvalue jsonPayload;
		jsonPayload["username"] = it.first;
		jsonPayload["score"] = it.second.GetPersonalScore();
		std::string jsonString = jsonPayload.dump();

		auto response = cpr::Put(
			cpr::Url{ "http://localhost:18080/profile/addGameToGameHistory" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } }
		);

	}
}

LobbyState Game::GetLobbyState()
{
	return m_lobbyState;
}


auto Game:: getHighestScorer() {
	
	auto comparator = [](const auto& playerPair1, const auto& playerPair2) {
		return playerPair1.second.GetPersonalScore() > playerPair2.second.GetPersonalScore();
		};

	auto maxScoreIt = std::max_element(m_players.begin(), m_players.end(), comparator);

	return maxScoreIt;
}