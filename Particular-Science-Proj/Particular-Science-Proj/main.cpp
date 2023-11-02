//test main for pull, modify as needed
#include <iostream>
#include <vector>
#include "Player.h"
void Score_Player_Guessing(Player& p,int timp)
{
	if (timp == 60)
	{
		p.UpdateScore(p.GetPersonalScore() - 100);
	}
	else if (timp < 30)
	{
		p.UpdateScore(p.GetPersonalScore() + 100);
	}
	else
	{
		int s = (60 - timp) * 100 / 30;
		p.UpdateScore(p.GetPersonalScore() + s);
	}
}

void Score_Player_Drawing(Player& p, std::vector<Player>players_guessing)
{
	float average_time;
	int sum_times=0;

	for (int i = 0; i < players_guessing.size(); i++)
	{
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



int main() {
	return 0;
}