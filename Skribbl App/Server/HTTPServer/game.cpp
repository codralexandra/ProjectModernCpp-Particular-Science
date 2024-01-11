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

Game::Game(const std::unordered_map<std::string, Player>& players,const Difficulty& difficulty,const std::vector<Word>& words,const std::string& date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }
{
}

void Game::SetPlayers(const std::unordered_map<std::string,Player>& players)
{
	m_players = players;
}

void Game::SetWords(const std::vector<Word>& words)
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


std::unordered_map<std::string, Player> Game::GetPlayers() const
{
	return m_players;
}

std::vector<Word> Game::GetWords() const
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


void Game::StartGame(crow::SimpleApp& m_app)
{
	//start game
	for (int i = 0; i < m_rounds; i++)
	{
		m_round.reset(new Round);
		m_round->StartRound(m_players, m_words, m_app);

	}
	//stop game
	
	

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
	//clasament
}

LobbyState Game::GetLobbyState()
{
	return m_lobbyState;
}


auto Game:: GetHighestScorer() {
	
	auto comparator = [](const auto& playerPair1, const auto& playerPair2) {
		return playerPair1.second.GetPersonalScore() > playerPair2.second.GetPersonalScore();
		};

	auto maxScoreIt = std::max_element(m_players.begin(), m_players.end(), comparator);

	return maxScoreIt;
}