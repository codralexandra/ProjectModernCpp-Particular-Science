#include "SubRound.h"

SubRound::SubRound()
{

}

void SubRound::SetWord(const std::string& cuv)
{
	std::cout << "Set Word apelata\n";
	this->word = cuv;
}

const std::string SubRound::GetWord() const
{
	return this->word;
}

void SubRound::StartSubRound()
{
	std::cout << "Start SubRound apelata\n";
	/*Scribble::Player p = this->GetDrawer();
	SetWord("table");*/

}


