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
		Game();
		Game(std::unordered_map<std::string,Player> players, Difficulty difficulty, std::vector<Word> words, std::string date);

		void setPlayers(const std::unordered_map<std::string,Player>& players);
		void setWords(const std::vector<Word>& words);
		void SetGameID(const uint16_t& id);
		void AddPlayer(const Player& p);
		void SetDifficulty(const Difficulty& difficulty);
		void SetLobbyState(const LobbyState& lobbystate);


		std::unordered_map<std::string,Player> getPlayers() const;
		std::vector<Word> getWords() const;
		uint16_t GetGameID() const;
		Difficulty GetDifficulty() const;
		void Start_Game(crow::SimpleApp& m_app);
		LobbyState GetLobbyState();

		

		auto getHighestScorer();
		

	private:
		std::unordered_map<std::string,Player> m_players;
		Difficulty m_difficulty;
		LobbyState m_lobbyState;
		static const uint16_t m_rounds = 4;
		std::vector<Word> m_words;
		std::unique_ptr<Round> m_round;
		uint16_t m_gameID;
	};

