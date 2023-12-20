#include "SubRound.h"
#include <iostream>

SubRound::SubRound()
{

}

void SubRound::SetWord(const Word& cuv)
{
	std::cout << "Set Word apelata\n";
	this->m_word = cuv;
}

 Word SubRound::GetWord() const
{
	return this->m_word;
}

void SubRound::StartSubRound( Player p)
{
	std::cout << "Start SubRound apelata\n";
	const double timeLimit = 45.0;
	m_timer.start();
	while (m_timer.elapsedSeconds() < timeLimit)
	{
		//check
		if (m_timer.elapsedSeconds() == 30.0)
		{
			m_word.ShowHint();
		}
		
		else if (m_timer.elapsedSeconds() == 40.0)
		{
			m_word.ShowHint();
		}
		
		else if (m_timer.elapsedSeconds() == 50.0)
		{
			m_word.ShowHint();
		}
		

	}
	m_timer.stop();




    //afisare cuv in functie de rol jucator
	//start timer
	//desen/ghicit
	//stop timer-> dispare widget
	//end subround
}


