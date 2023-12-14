#include "SubRound.h"
#include <iostream>

SubRound::SubRound()
{

}

void SubRound::SetWord(const std::string& cuv)
{
	std::cout << "Set Word apelata\n";
	this->m_word = cuv;
}

const std::string SubRound::GetWord() const
{
	return this->m_word;
}

void SubRound::StartSubRound(Scribble::Game& g)
{
	std::cout << "Start SubRound apelata\n";
	//Scribble::Player p = this->GetDrawer();
	//SetWord("table");
	


    //afisare cuv in functie de rol jucator
	//start timer
	//desen/ghicit
	//stop timer-> dispare widget
	//end subround
}


