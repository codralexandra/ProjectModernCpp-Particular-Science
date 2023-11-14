#include "SubRound.h"

SubRound::SubRound()
{

}

void SubRound::SetWord(const std::string& cuv)
{
	this->word = cuv;
}

const std::string SubRound::GetWord() const
{
	return this->word;
}

void SubRound::StartSubRound()
{

}

void SubRound::PrintWordToGuess()
{
	for (int i = 0; i < this->word.size(); i++)
	{
		std::cout << "_ ";
	}
	std::cout << std::endl;
}
