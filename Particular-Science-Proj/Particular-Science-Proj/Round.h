import game;
import player;
#include "SubRound.h"

class Round
{
public:
	Round();
	void StartRound(Scribble::Game& g);
	void SetDrawer(const Scribble::Player& p);
	Scribble::Player GetDrawer();

private:
	Scribble::Player m_CurrentDrawer;
	SubRound* sb;

};

