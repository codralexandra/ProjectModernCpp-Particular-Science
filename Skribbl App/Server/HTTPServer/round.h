#include "SubRound.h"
#include "player.h"
#include <memory>
#include <vector>
#include <crow.h>
#include <cpr/cpr.h>


class Round
{
public:
	Round();
	
	void StartRound( std::unordered_map<std::string,Player>& p, std::vector< Word>& word, crow::SimpleApp& m_app);
	void Score_Player_Drawing(Player& p, const std::unordered_map<std::string,Player>&players_guessing);
	void Score_Player_Guessing(std::unordered_map<std::string,Player>& p);

private:

	std::unique_ptr<SubRound> m_subRound;

};

