module game;
import <queue>;
import player;
using namespace Scribble;
import <iostream>;
import <vector>;
#include "difficulty.h";

Game::Game()
{
}

Game::Game(std::vector<Player> players, Difficulty difficulty, std::vector<std::string> words, std::string date) :
	m_players{ players }, m_difficulty{ difficulty }, m_words{ words }, m_date{ date }
{
}

void Game::setPlayers(std::vector<Player> players)
{
	m_players = players;
}

void Game::setWords(std::vector<std::string> words)
{
	m_words = words;
}


std::vector<Scribble::Player> Scribble::Game::getPlayers()
{
	return m_players;
}

std::vector<std::string> Game::getWords()
{
	return m_words;
}


void Game::Start_Game()
{
	std::cout << "Start Game apelata \n";
	int dim_runde = 4;
	for (int i = 0; i < dim_runde; i++)
	{
		r = new Round();
		r.start();
	}
	//stop game
	
}

Player Game::Winner()
{
	int maxim = 0;
	Player player_max;
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].GetPersonalScore() > maxim) {
			maxim = m_players[i].GetPersonalScore();
			player_max = m_players[i];
		}
	}
	return player_max;

}



//void Scribble::Game::updateHistoryPlayer() //recheck
//{
//	std::cout << "Update Hostory Player apelata\n";
//	std::queue<std::pair<uint16_t, std::string>> gameHistory;
//	for (auto& player : m_players)
//	{
//		gameHistory = player.GetGameHistory();
//		gameHistory.pop();
//		player.SetGameHistory(gameHistory);
//		player.AddGameToGameHistory({ player.GetPersonalBest(),player. });
//	}
//}
