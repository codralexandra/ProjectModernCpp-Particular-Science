#include <string>
#include "player.h"
#include "Timer.h"
#include "Word.h"

class SubRound
{
public:

	//constructors and destructors
	SubRound();
	SubRound(const Word& word, const Timer& timer);
	~SubRound() = default;
	SubRound(const SubRound& other);
	SubRound(const SubRound&& other) noexcept;


	//operators
	SubRound& operator=(const SubRound& other);
	SubRound& operator=(SubRound&& other);


	//setter
	void SetWord(const Word& cuv);

	//getter
	Word GetWord()const;


	void StartSubRound(const Player& p, const Word& word);


private:
	Word m_word;
	Timer m_timer;
};

