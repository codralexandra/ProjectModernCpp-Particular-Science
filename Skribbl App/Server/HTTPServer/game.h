#pragma once
#include <iostream>
#include <vector>
#include "Difficulty.h"
#include "player.h"
#include "round.h"

 class Game
	{
	public:
		Game();
		Game(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date);

		void setPlayers(std::vector<Player> players);
		void setWords(std::vector<std::string> words);


		std::vector<Player> getPlayers();
		std::vector<std::string> getWords();


		void Start_Game();

		Player Winner();
		//void updateHistoryPlayer();

	private:
		std::vector<Player> m_players;
		Difficulty m_difficulty;
		static const uint16_t m_rounds = 4;
		std::vector<std::string> m_words;
		Round r;
	};

