#include "SubRound.h"
#include "player.h"
#include <memory>
#include <vector>


class Round
{
public:
	Round();
	
	void StartRound( std::vector<Player>& p, std::vector< std::string>& word);
	void Score_Player_Drawing(Player& p, const std::vector<Player>&players_guessing);
	void Score_Player_Guessing(std::vector<Player>& p);

private:

	std::unique_ptr<SubRound> m_subRound;

};

