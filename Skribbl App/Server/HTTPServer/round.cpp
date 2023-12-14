#include "Round.h"

Round::Round()
{
	this->m_CurrentDrawer = new Scribble::Player;
}

void Round::StartRound(Scribble::Game& g)
{
	std::cout << "Start ROUND apelata\n";
	for (int i = 0; i < g.getPlayers().size(); i++)
	{
		sb = new SubRound();
		g.getPlayers()[i].SetIsDrawer(true);
		sb->StartSubRound(g);
		Score_Player_Drawing(g.getPlayers()[i], g.getPlayers());
		Score_Player_Guessing(g.getPlayers());
		g.getPlayers()[i].SetIsDrawer(false);
		
	}
	//end round
}

void Roound::Score_Player_Drawing(Player& p, std::vector<Player>players_guessing)
{
	std::cout << "Score Drawing apelata\n";
	float average_time;
	int sum_times = 0;

	for (int i = 0; i < players_guessing.size(); i++)
	{
		if (players_guessing[i].GetIsDrawer() == false)
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
void Round::Score_Player_Guessing(std::vector<Player>& p)
{
	for (auto player : p)
	{
		if (player.GetIsDrawer() == false)
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
	}
}