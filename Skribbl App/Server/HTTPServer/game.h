#pragma once
#include <iostream>
#include <vector>
#include "Difficulty.h"
#include "player.h"
#include "round.h"
#include <memory>
#include "Word.h"
#include "lobbystate.h"
#include <crow.h>
#include <cpr/cpr.h>
#include <unordered_map>

 class Game
	{
	public:
		//constructors
		Game();
		~Game() = default;
		Game(const std::unordered_map<std::string,Player>& players,const Difficulty& difficulty, const std::vector<Word>& words, const std::string& date);
		Game(const Game& other);
		Game(Game&& other);

		//setter
		void SetPlayers(const std::unordered_map<std::string,Player>& players);
		void SetWords(const std::vector<Word>& words);
		void SetGameID(const uint16_t& id);
		void SetDifficulty(const Difficulty& difficulty);
		void SetLobbyState(const LobbyState& lobbystate);
		void SetPlayerHasGuessed(const std::string& username, bool hasGuessed);
		void SetPlayerReceivedPixels(const std::string& username, bool received);

		//operators
		Game& operator=(const Game& other);
		//Game& operator=(Game&& other)noexcept;

		//getter
		std::unordered_map<std::string,Player> GetPlayers() const;
		std::vector<Word> GetWords() const;
		uint16_t GetGameID() const;
		Difficulty GetDifficulty() const;
		LobbyState GetLobbyState() const;
		Round& GetRoundRef();

		auto GetHighestScorer();
		void AddPlayer(const Player& p);
		void StartGame(crow::SimpleApp& m_app);

		//updates
		void UpdateWords();
		void UpdatePersonalBest();


	private:
		std::unordered_map<std::string,Player> m_players;
		Difficulty m_difficulty;
		LobbyState m_lobbyState;
		static constexpr uint16_t m_rounds = 4;
		std::vector<Word> m_words;
		std::unique_ptr<Round> m_round;
		uint16_t m_gameID;
	};

