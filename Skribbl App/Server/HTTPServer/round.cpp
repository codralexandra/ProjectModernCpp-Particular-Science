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

void Round::StartRound(std::unordered_map<std::string,Player>& p,  std::vector< Word>& word, crow::SimpleApp& m_app)
{
	//check the random part!!!


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

		it.second.SetIsDrawer(true);
		std::cout << "\n Role set \n";
		std::cout << "Start Game apelata \n";
		crow::json::wvalue jsonPayload;
		jsonPayload["word"] = word[randPosition].getValue();
		std::string jsonString = jsonPayload.dump();

		auto response = cpr::Put(
			cpr::Url{ "http://localhost:18080/game/getword" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } }
		);
		m_subRound->StartSubRound(it.second,word[randPosition]);
		
		word.erase(word.begin() + randPosition, word.begin() + randPosition + 1);
		t.start();
		//reset la timer
		while (t.elapsedSeconds() < timeLimit){}
		t.stop();

		Score_Player_Drawing(it.second, p);
		Score_Player_Guessing(p);

		it.second.SetIsDrawer(false);
		
	}
	//end round
}

void Round::Score_Player_Drawing(Player& p,const std::unordered_map<std::string,Player>&players_guessing)
{
	std::cout << "Score Drawing apelata\n";

	auto firstIt = players_guessing.begin();
	auto lastIt = players_guessing.end();

	auto totalScore = std::accumulate(firstIt, lastIt, 0,
		[](int sum, const std::pair<const std::string, Player>& playerPair) {
			const Player& player = playerPair.second;
			return (!player.GetIsDrawer()) ? sum + player.GetPersonalScore() : sum;
		}
	);
	
	if (totalScore == 60 * players_guessing.size())
		p.SetScore(p.GetPersonalScore() - 100);
	else
	{
		p.SetScore(p.GetPersonalScore() + (60 - (totalScore / players_guessing.size())) * 100 / 60);

	}
}

void Round::Score_Player_Guessing(std::unordered_map<std::string,Player>& p)
{
	std::cout << "Score guessing called\n";
	for (auto &player : p)
	{
		if (player.second.GetIsDrawer() == false)
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
	}
}