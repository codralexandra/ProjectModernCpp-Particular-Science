#pragma once
#include <iostream>
#include <vector>
#include "Difficulty.h"
#include "player.h"
#include "round.h"
#include <memory>

 class Game
	{
	public:
		Game();
		Game(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date);

		void setPlayers(std::vector<Player> players);
		void setWords(std::vector<std::string> words);
		void SetGameID(uint16_t id);

		std::vector<Player> getPlayers();
		std::vector<std::string> getWords();
		uint16_t GetGameID();

		void Start_Game();

		Player Winner();
		

	private:
		std::vector<Player> m_players;
		Difficulty m_difficulty;
		static const uint16_t m_rounds = 4;
		std::vector<std::string> m_words;
		std::unique_ptr<Round> m_round;
		uint16_t m_gameID;
	};

