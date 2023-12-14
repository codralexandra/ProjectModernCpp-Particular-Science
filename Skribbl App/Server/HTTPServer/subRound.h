#include <string>

import player;

#include "Timer.h"
class SubRound
{
public:
	SubRound();


	void SetWord(const std::string& cuv);
	const std::string GetWord()const;
	void StartSubRound(Scribble::Player p);


private:
	std::string m_word;
	Timer m_timer;
};

