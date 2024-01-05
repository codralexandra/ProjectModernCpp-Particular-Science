#include "Round.h"
#include <iostream>
#include "Timer.h"
#include <functional>
#include <ranges>
#include <numeric>
#include <random>
#include <cstdint>

Round::Round()
{
	
}

void Round::StartRound(std::vector<Player>& p,  std::vector< Word>& word)
{
	//check the random part!!!


	Timer t;
	std::random_device rd;
	std::mt19937 gen(rd());
	
	uint16_t randPosition;
	const double timeLimit = 3.0;

	std::cout << "Start ROUND apelata\n";
	for (int i = 0; i < p.size(); i++)
	{
		std::uniform_real_distribution<> dist(0, word.size()); 
		m_subRound.reset(new SubRound);

		randPosition = dist(gen);

		p[i].SetIsDrawer(true);
		m_subRound->StartSubRound(p[i],word[randPosition]);
		
		word.erase(word.begin() + randPosition, word.begin() + randPosition + 1);
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

void Round::Score_Player_Drawing(Player& p,const std::vector<Player>&players_guessing)
{
	std::cout << "Score Drawing apelata\n";

	auto firstIt{ std::ranges::cbegin(players_guessing) };
	auto lastIt{ std::ranges::cend(players_guessing) };
	
	auto totalScore{ std::accumulate(firstIt,lastIt,0,
		[](int sum, const Player& player) {
			return (!player.GetIsDrawer()) ? sum + player.GetPersonalScore() : sum;
		}
	) 
	};
	
	if (totalScore == 60 * players_guessing.size())
		p.SetScore(p.GetPersonalScore() - 100);
	else
	{
		p.SetScore(p.GetPersonalScore() + (60 - (totalScore / players_guessing.size())) * 100 / 60);

	}
}

void Round::Score_Player_Guessing(std::vector<Player>& p)
{
	std::cout << "Score guessing called\n";
	for (auto &player : p)
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
				player.SetScore(player.GetPersonalScore() + ((60 - player.GetTimeGuessed()) * 100 / 30));
			}
		}
	}
}