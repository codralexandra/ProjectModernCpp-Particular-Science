#include "SubRound.h"
import player;
#include <vector>
//import game;

class Round
{
public:
	Round();
	
	//void StartRound(Scribble::Game& g);
	void Score_Player_Drawing(Scribble::Player& p, std::vector<Scribble::Player>players_guessing);
	void Score_Player_Guessing(std::vector<Scribble::Player>& p);

private:

	SubRound* sb;

};

