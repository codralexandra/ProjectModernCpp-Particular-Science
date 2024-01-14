#include <string>
#include "player.h"
#include "Timer.h"
#include "Word.h"
#include "difficulty.h"

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
	SubRound& operator=(SubRound&& other)noexcept;


	//setter
	void SetWord(const Word& cuv);
	void SetGuessed(bool value);
	void SetTime(const double& time);

	//getter
	Word GetWord()const;
	bool GetGuessed()const;
	double GetTimeGuessed()const;


	void StartSubRound(Player& p, Word& word,const Difficulty& dif);
	void ShowHint(Word& word);


private:
	bool m_guessed;
	double m_timeGuessed;
	Word m_word;
	Timer m_timer;
};

