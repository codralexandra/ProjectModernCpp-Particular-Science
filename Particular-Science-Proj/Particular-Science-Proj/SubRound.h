#include <string>
using namespace Scribble;
import game;

class SubRound
{
public:
	SubRound();
	void SetWord(const std::string& cuv);
	const std::string GetWord()const;
	void StartSubRound(Scribble::Game& g);
	

private:
	std::string word;
	//Qtimer time;
};

