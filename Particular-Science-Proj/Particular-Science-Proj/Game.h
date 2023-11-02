#pragma once
#include <vector>
#include "Player.h"
#include "Difficulty.h"

class Game
{
public:
	Game();
	Game(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date);

	void setPlayers(std::vector<Player> players);
	void setWords(std::vector<std::string> words);
	void setDate(std::string date);

	std::vector<Player> getPlayers();
	std::vector<std::string> getWords();
	std::string getDate();

	
	
private:
	std::vector<Player> m_players;
	Difficulty m_difficulty;
	static const uint16_t m_rounds = 4;
	std::vector<std::string> m_words;
	std::string m_date; //regex check or make class

};

