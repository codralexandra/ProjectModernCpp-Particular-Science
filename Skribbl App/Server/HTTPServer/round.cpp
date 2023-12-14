#include "Round.h"

Round::Round()
{
	this->m_CurrentDrawer = new Scribble::Player;
}

void Round::StartRound(Scribble::Game& g)
{
	std::cout << "Start ROUND apelata\n";
	for (int i = 0; i < g.getPlayers().size(); i++)
	{
		sb = new SubRound();
		SetDrawer(g.getPlayers()[i]);
		sb->StartSubRound(g);
		//calcul scor
		// player curent not drawer anymore
		
	}
	//end round
}

void Round::SetDrawer(const Scribble::Player& p)
{
	std::cout << "SetDrawer apelata\n";
	this->m_CurrentDrawer = p;
}

Scribble::Player Round::GetDrawer()
{
	return this->m_CurrentDrawer;
}


