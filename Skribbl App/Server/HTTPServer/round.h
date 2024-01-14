#include "SubRound.h"
#include "player.h"
#include <memory>
#include <vector>
#include <crow.h>
#include <cpr/cpr.h>
#include "difficulty.h"


class Round
{
public:
	//constructors
	Round();
	~Round() = default;

	//getter
	SubRound& GetSubRoundRef();


	//scores
	void Score_Player_Drawing(Player& p,  std::unordered_map<std::string,Player>&players_guessing);
	void Score_Player_Guessing(std::unordered_map<std::string,Player>& p);

	void StartRound(std::unordered_map<std::string, Player>& p, std::vector< Word>& word, crow::SimpleApp& m_app,const Difficulty& dif);

private:

	std::unique_ptr<SubRound> m_subRound;

};

