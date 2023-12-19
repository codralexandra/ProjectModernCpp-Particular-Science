#include "Round.h"
#include <iostream>
#include "Timer.h"

Round::Round()
{
	
}

void Round::StartRound(std::vector<Player>& p)
{
	Timer t;
	const double timeLimit = 3.0;
	std::cout << "Start ROUND apelata\n";
	for (int i = 0; i < p.size(); i++)
	{
		m_subRound.reset(new SubRound);

		p[i].SetIsDrawer(true);
		m_subRound->StartSubRound(p[i]);
		
		t.start();
		//reset la timer
		while (t.elapsedSeconds() < timeLimit){}
		t.stop();

		Score_Player_Drawing(p[i], p);
		Score_Player_Guessing(p);

		p[i].SetIsDrawer(false);
		
	}
	//end round
}

void Round::Score_Player_Drawing(Player& p, std::vector<Player>players_guessing)
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
	std::cout << "Score guessing called\n";
	for (auto player : p)
	{
		if (player.GetIsDrawer() == false)
		{
			if (player.GetTimeGuessed() == 60)
			{
				player.SetScore(player.GetPersonalScore() - 50);
			}
			else if (player.GetTimeGuessed() < 30)
			{
				player.SetScore(player.GetPersonalScore() + 100);
			}
			else
			{
				int s = (60 - player.GetTimeGuessed()) * 100 / 30;
				player.SetScore(player.GetPersonalScore() + s);
			}
		}
	}
}