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

void Game::Score_Player_Drawing(Player& p, std::vector<Player>players_guessing)
{
	std::cout << "Score Drawing apelata\n";
	float average_time;
	int sum_times = 0;

	for (int i = 0; i < players_guessing.size(); i++)
	{
		if (players_guessing[i].GetIsDrawing() == false)
			sum_times = players_guessing[i].GetTimeGuessed() + sum_times;
	}

	if (sum_times == 60 * players_guessing.size())
		p.SetScore(p.GetPersonalScore() - 100);
	else
	{
		average_time = sum_times / players_guessing.size();
		p.SetScore(p.GetPersonalScore() + (60 - average_time) * 100 / 60);

	}
}
void Game::Score_Player_Guessing(Scribble::Player& p, int timp)
{
	if (timp == 60)
	{
		p.SetScore(p.GetPersonalScore() - 50);
	}
	else if (timp < 30)
	{
		p.SetScore(p.GetPersonalScore() + 100);
	}
	else
	{
		int s = (60 - timp) * 100 / 30;
		p.SetScore(p.GetPersonalScore() + s);
	}
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
