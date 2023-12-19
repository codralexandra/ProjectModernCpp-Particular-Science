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

void SubRound::StartSubRound( Player p)
{
	std::cout << "Start SubRound apelata\n";
	const double timeLimit = 2.0;
	m_timer.start();
	while (m_timer.elapsedSeconds() < timeLimit)
	{
		

	}
	m_timer.stop();




    //afisare cuv in functie de rol jucator
	//start timer
	//desen/ghicit
	//stop timer-> dispare widget
	//end subround
}


