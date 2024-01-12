#include "SubRound.h"
#include <iostream>
#include <crow.h>
#include <cpr/cpr.h>

SubRound::SubRound()
{
	//empty
}

SubRound::SubRound(const Word& word, const Timer& timer) : m_timer(timer), m_word(word)
{
	//empty
}

SubRound::SubRound(const SubRound& other)
{
	m_word = other.m_word;
	m_timer = other.m_timer;
}

SubRound::SubRound(const SubRound&& other) noexcept
{
	m_word = std::move(other.m_word);
	m_timer = std::move(other.m_timer);
}

SubRound& SubRound::operator=(const SubRound& other)
{
	this->m_word = other.m_word;
	this->m_timer = other.m_timer;
	return*this;
}

//SubRound& SubRound::operator=(SubRound&& other)noexcept
//{
//	if (this != &other) {
//		// Move-assign the Word object
//		m_word = std::move(other.m_word);
//
//		// Move-assign the Timer object
//		m_timer = std::move(other.m_timer);
//
//	}
//	return *this;
//}

void SubRound::SetWord(const Word& cuv)
{
	std::cout << "Set Word apelata\n";
	this->m_word = cuv;
}

Word SubRound::GetWord() const
{
	return this->m_word;
}

void SubRound::StartSubRound(const Player& p,Word& word)
{
	std::cout << "Start SubRound apelata\n";
	const double timeLimit = 60.0;

	m_timer.start();
	while (m_timer.elapsedSeconds() < timeLimit)
	{
		//check

		if (m_timer.elapsedSeconds() == 30.0)
		{
			ShowHint(word);
		}

		else if (m_timer.elapsedSeconds() == 40.0)
		{
			ShowHint(word);
		}

		else if (m_timer.elapsedSeconds() == 50.0)
		{
			ShowHint(word);
		}


	}
	m_timer.stop();

}

void SubRound::ShowHint(Word & word)
{
	std::cout << "ShowHint apelata\n";
	if (word.GetNumberHint() > 0)
	{
		std::cout << "Take a hint\n";
		srand(0);
		bool ok = false;
		int randomPosition = rand() % word.GetValueAux().size();
		while (word.GetValueAux()[randomPosition] != '_')
		{
			randomPosition = rand() % word.GetValueAux().size();
		}
		std::cout << "This is the hint\n";
		std::cout << randomPosition << " " << word.GetValue()[randomPosition] << std::endl;
		std::string newAux = word.GetValueAux();
		newAux[randomPosition] = word.GetValue()[randomPosition];
		std::cout << "\nnewAux:" << newAux<<"\n";
		
		word.SetNumberHints(word.GetNumberHint()-1);
		word.UpdateAux(newAux);
	}
	crow::json::wvalue jsonPayload;
	jsonPayload["currentword"] = word.GetValueAux();
	std::cout << "\n" << word.GetValueAux() << "\n";
	jsonPayload["wordDrawer"] = word.GetValue();
	std::string jsonString = jsonPayload.dump();

	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/game/getword" },
		cpr::Body{ jsonString },
		cpr::Header{ { "Content-Type", "application/json" } }
	);
	std::cout << "This is the word with hints: " << word.GetValueAux() << std::endl;
	

}
