#pragma once

import game;
import player;


class Round: 
{
public:
	Round();
	void StartRound();
	void SetDrawer(const Scribble::Player& p);
	Scribble::Player GetDrawer();

private:
	Scribble::Player m_CurrentDrawer;

};

