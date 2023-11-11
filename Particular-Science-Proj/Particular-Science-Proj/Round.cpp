#include "Round.h"

Round::Round()
{
	this->m_CurrentDrawer = new Player();
}

void Round::StartRound()
{
	for (int i = 0; i < this->m_players.size(); i++)
	{
		SetDrawer(m_players[i]);

	}
}

void Round::SetDrawer(const Player& p)
{
	this->m_CurrentDrawer = p;
}

Player Round::GetDrawer()
{
	return this->m_CurrentDrawer;
}


