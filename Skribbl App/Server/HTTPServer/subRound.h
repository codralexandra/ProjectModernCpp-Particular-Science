#include <string>

#include "player.h"

#include "Timer.h"
#include "Word.h"

class SubRound
{
public:
	SubRound();


	void SetWord(const Word& cuv);
	Word GetWord()const;
	void StartSubRound(Player p);


private:
	Word m_word;
	Timer m_timer;
};

