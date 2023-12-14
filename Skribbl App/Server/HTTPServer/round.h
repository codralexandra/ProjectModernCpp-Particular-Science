#include "SubRound.h"
import player;
using namespace Scribble;
#include <vector>
//import game;

class Round
{
public:
	Round();
	
	void StartRound(std::vector<Scribble::Player>& p);
	void Score_Player_Drawing(Scribble::Player& p, std::vector<Scribble::Player>players_guessing);
	void Score_Player_Guessing(std::vector<Scribble::Player>& p);

private:

	SubRound* sb;

};

