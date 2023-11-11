#pragma once
import player;
import game;
class Round:public Game
{
public:
	Round();
	void StartRound();
	void SetDrawer(const Player& p);
	Player GetDrawer();

private:
	Player m_CurrentDrawer;

};

