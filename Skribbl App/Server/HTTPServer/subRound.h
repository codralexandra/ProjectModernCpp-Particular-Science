#include <string>
using namespace Scribble;
import game;
#include "Timer.h"
class SubRound
{
public:
	SubRound();
	void SetWord(const std::string& cuv);
	const std::string GetWord()const;
	void StartSubRound(Scribble::Game& g);


private:
	std::string m_word;
	Timer* m_timer;
};

