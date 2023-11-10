module game;
using Scribble::Game;

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

void Game::setDate(std::string date)
{
	m_date = date;
}



std::vector<Scribble::Player> Scribble::Game::getPlayers()
{
	return m_players;
}

std::vector<std::string> Game::getWords()
{
	return m_words;
}

std::string Game::getDate()
{
	return m_date;
}

void Game::Start_Game()
{
	int dim_runde = 4;
	for (int i = 0; i < dim_runde; i++)
	{
		for (auto player : m_players)
		{
			player.SetIsDrawing(true);
			//random word choice
			Score_Player_Drawing(player, m_players);
			//print result
		}
		//print score after round ends (add timer)
	}
	//print score after game
	//stop game
	//print winner
	int maxim = 0;
	Player player_max;
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].GetPersonalScore() > maxim) {
			maxim = m_players[i].GetPersonalScore();
			player_max = m_players[i];
		}
	}
	std::cout << "Winner: " << player_max;
}

void Game::Score_Player_Drawing(Player& p, std::vector<Player>players_guessing)
{
	float average_time;
	int sum_times = 0;

	for (int i = 0; i < players_guessing.size(); i++)
	{
		if (players_guessing[i].GetIsDrawing() == false)
			sum_times = players_guessing[i].GetTimeGuessed() + sum_times;
	}

	if (sum_times == 60 * players_guessing.size())
		p.UpdateScore(p.GetPersonalScore() - 100);
	else
	{
		average_time = sum_times / players_guessing.size();
		p.UpdateScore(p.GetPersonalScore() + (60 - average_time) * 100 / 60);

	}
}