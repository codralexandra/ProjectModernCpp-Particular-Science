#include "Round.h"
#include <iostream>

Round::Round()
{
	
}

void Round::StartRound(std::vector<Scribble::Player>& p)
{
	std::cout << "Start ROUND apelata\n";
	for (int i = 0; i < p.size(); i++)
	{
		sb = new SubRound();
		p[i].SetIsDrawing(true);
		//sb->StartSubRound(g);
		Score_Player_Drawing(p[i], p);
		Score_Player_Guessing(p);
		p[i].SetIsDrawing(false);
		
	}
	//end round
}

void Round::Score_Player_Drawing(Scribble::Player& p, std::vector<Scribble::Player>players_guessing)
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

void Round::Score_Player_Guessing(std::vector<Scribble::Player>& p)
{
	for (auto player : p)
	{
		if (player.GetIsDrawing() == false)
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