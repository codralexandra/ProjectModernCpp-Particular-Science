#pragma once
#include <iostream>
#include <vector>
#include "Difficulty.h"
#include "player.h"
#include "round.h"
#include <memory>
#include "Word.h"

 class Game
	{
	public:
		Game();
		Game(std::vector<Player> players, Difficulty difficulty, std::vector<Word> words, std::string date);

		void setPlayers(const std::vector<Player>& players);
		void setWords(const std::vector<Word>& words);
		void SetGameID(const uint16_t& id);
		void AddPlayer(const Player& p);
		void SetDifficulty(const Difficulty& difficulty);


		std::vector<Player> getPlayers() const;
		std::vector<Word> getWords() const;
		uint16_t GetGameID() const;
		Difficulty GetDifficulty() const;
		void Start_Game();

		Player Winner();
		

	private:
		std::vector<Player> m_players;
		Difficulty m_difficulty;
		static const uint16_t m_rounds = 4;
		std::vector<Word> m_words;
		std::unique_ptr<Round> m_round;
		uint16_t m_gameID;
	};

