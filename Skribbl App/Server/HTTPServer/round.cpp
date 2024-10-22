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

SubRound& Round::GetSubRoundRef()
{
	return *m_subRound;
}

void Round::StartRound(std::unordered_map<std::string,Player>& p,  std::vector< Word>& word, crow::SimpleApp& m_app,const Difficulty& dif)
{
	Timer t;
	std::random_device rd;
	std::mt19937 gen(rd());
	
	uint16_t randPosition;
	const double timeLimit = 3.0;

	std::cout << "Start ROUND apelata\n";
	for (auto& it:p)
	{
		std::uniform_real_distribution<> dist(0, word.size()); 
		m_subRound.reset(new SubRound);

		randPosition = dist(gen);
		int random = randPosition;

		std::cout << "\n Role set \n";
		std::cout << "Start Game apelata \n";

		crow::json::wvalue jsonPayload;
		std::cout << "\n" << word[random].GetValue() << "\n";
		std::cout << "\n" << word[random].GetValueAux() << "\n";
		jsonPayload["wordDrawer"] = word[random].GetValue();
		jsonPayload["currentword"] = word[random].GetValueAux();
		std::string jsonString = jsonPayload.dump();

		auto response = cpr::Put(
			cpr::Url{ "http://localhost:18080/game/getword" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } }
		);
		it.second.SetIsDrawer(true);
		for (auto& player : p)
		{
			player.second.SetHasGuessed(false);
			player.second.SetTimeGuessed(60.0);
		}
		m_subRound->StartSubRound(it.second,word[random],dif);
		
		word.erase(word.begin() + random, word.begin() + random + 1);
		t.start();
		//reset la timer
		while (t.elapsedSeconds() < timeLimit){}
		t.stop();

		Score_Player_Guessing(p);
		Score_Player_Drawing(it.second, p);
		

		it.second.SetIsDrawer(false);
		
	}
	//end round
}

void Round::Score_Player_Drawing(Player& p, std::unordered_map<std::string,Player>&players_guessing)
{
	
	auto firstIt = std::ranges::begin(players_guessing);
	auto lastIt = std::ranges::end(players_guessing);

	auto totalTime = std::accumulate(firstIt, lastIt, 0.0,
		[](double sum, const std::pair<const std::string, Player>& playerPair) {
			const Player& player = playerPair.second;
			return (player.GetIsDrawer()) ? sum + player.GetTimeGuessed() : sum;
		}
	);
	
	if (totalTime==(60.0*(players_guessing.size()-1)))
		p.SetScore(p.GetPersonalScore() - 100);
	else
	{
		p.SetScore(p.GetPersonalScore() + (60 - (totalTime / (players_guessing.size()-1))) * 100 / 60);

	}
	std::cout << p.GetPersonalScore();
}

void Round::Score_Player_Guessing(std::unordered_map<std::string,Player>& p)
{
	std::cout << "Score guessing called\n";
	for (auto &player : p)
	{
		std::cout << "Time for player: " << player.second.GetUsername() << " " << player.second.GetTimeGuessed()<<" and last score\n";
		std::cout << player.second.GetPersonalScore()<<std::endl;
		if (player.second.GetIsDrawer() == true)
		{
			if (player.second.GetTimeGuessed() == 60)
			{
				player.second.SetScore(player.second.GetPersonalScore() - 50);
			}
			else if (player.second.GetTimeGuessed() < 30)
			{
				player.second.SetScore(player.second.GetPersonalScore() + 100);
			}
			else
			{
				player.second.SetScore(player.second.GetPersonalScore() + ((60 - player.second.GetTimeGuessed()) * 100 / 30));
			}
		}
		std::cout << player.second.GetPersonalScore();
	}
}