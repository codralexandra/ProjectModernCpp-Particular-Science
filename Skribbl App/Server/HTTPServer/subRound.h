#include <string>
#include "player.h"
#include "Timer.h"
#include "Word.h"

class SubRound
{
public:

	//constructors
	SubRound();
	

	//setter
	void SetWord(const Word& cuv);

	//getter
	Word GetWord()const;


	void StartSubRound(const Player& p,const Word& word);


private:
	Word m_word;
	Timer m_timer;
};

