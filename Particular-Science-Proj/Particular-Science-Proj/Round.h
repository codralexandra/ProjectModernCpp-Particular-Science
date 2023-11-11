#pragma once
import player;
import game;
class Round //public Game:
{
public:
	Round();
	void StartRound();
	void SetDrawer(const Scribble::Player& p);
	Scribble::Player GetDrawer();

private:
	Scribble::Player m_CurrentDrawer;

};

