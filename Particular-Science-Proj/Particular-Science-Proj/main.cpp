//test main for pull, modify as needed
#include <iostream>
#include <vector>
import player;

void Score_Player_Guessing(Scribble::Player& p,int timp)
{
	if (timp == 60)
	{
		p.UpdateScore(p.GetPersonalScore() - 50);
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

int main() {
	return 0;
}