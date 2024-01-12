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

Game::Game(const Game& other)
{
	m_players = other.m_players;
	m_difficulty = other.m_difficulty;
	m_lobbyState = other.m_lobbyState;
	m_words = other.m_words;
	//m_round = (other.m_round) ? std::make_unique<Round>(*other.m_round) : nullptr;
	m_gameID = other.m_gameID;

}

Game::Game(Game&& other)
{
	m_players = std::move(other.m_players);
	m_difficulty = std::move(other.m_difficulty);
	m_lobbyState = std::move(other.m_lobbyState);
	
	m_words = std::move(other.m_words);

	// Move the ownership of 'other.m_round' to 'm_round'
	m_round = std::move(other.m_round);

	m_gameID = other.m_gameID;
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

void Game::SetPlayerHasGuessed(const std::string& username,bool hasGuessed, const uint16_t& time)
{
	m_players[username].SetHasGuessed(hasGuessed);
	//m_players[username].SetTimeGuessed(time);
}

Game& Game::operator=(const Game& other)
{
	if (this != &other) {
		// Release resources owned by 'this' (if needed)
		// ...

		// Copy the values of members from 'other' to 'this'
		m_players = other.m_players;
		m_difficulty = other.m_difficulty;
		m_lobbyState = other.m_lobbyState;
		m_words = other.m_words;

		// Optionally, create a new Round based on 'other.m_round' (deep copy)
		//m_round = (other.m_round) ? std::make_unique<Round>(*other.m_round) : nullptr;

		m_gameID = other.m_gameID;

		// Optionally, copy other members if needed
		// ...
	}
	return *this;
}

//Game& Game::operator=(Game&& other) noexcept
//{
//	if (this != &other) {
//		// Release resources owned by 'this' (if needed)
//		// ...
//
//		// Move values from 'other' to 'this'
//		m_players = std::move(other.m_players);
//		m_difficulty = std::move(other.m_difficulty);
//		m_lobbyState = std::move(other.m_lobbyState);
//		m_words = std::move(other.m_words);
//
//		// Move the ownership of 'other.m_round' to 'm_round'
//		m_round = std::move(other.m_round);
//
//		m_gameID = other.m_gameID;
//
//		// Optionally, move other members if needed
//		// ...
//	}
//	return *this;
//}


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

void Game::UpdateWords()
{
	for (auto& word : m_words)
	{
		word.SetAuxiliar(word.GetValue());
		word.SetNumberHints(word.GetValue());
	}

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