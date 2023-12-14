import game;
import player;
#include "SubRound.h"

class Round
{
public:
	Round();
	void StartRound(Scribble::Game& g);
	void Score_Player_Drawing(Player& p, std::vector<Player>players_guessing);
	void Score_Player_Guessing(Scribble::Player& p, int timp);

private:

	SubRound* sb;

};

