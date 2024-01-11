#include "SubRound.h"
#include <iostream>

SubRound::SubRound()
{
	//empty
}

SubRound::SubRound(const Word& word, const Timer& timer) : m_timer(timer), m_word(word)
{
	//empty
}

SubRound::SubRound(const SubRound& other)
{
	m_word = other.m_word;
	m_timer = other.m_timer;
}

SubRound::SubRound(const SubRound&& other) noexcept
{
	m_word = std::move(other.m_word);
	m_timer = std::move(other.m_timer);
}

SubRound& SubRound::operator=(const SubRound& other)
{
	this->m_word = other.m_word;
	this->m_timer = other.m_timer;
	return*this;
}

SubRound& SubRound::operator=(SubRound&& other)
{
	if (this != &other) {
		// Move-assign the Word object
		m_word = std::move(other.m_word);

		// Move-assign the Timer object
		m_timer = std::move(other.m_timer);

	}
	return *this;
}

void SubRound::SetWord(const Word& cuv)
{
	std::cout << "Set Word apelata\n";
	this->m_word = cuv;
}

Word SubRound::GetWord() const
{
	return this->m_word;
}

void SubRound::StartSubRound(const Player& p, const Word& word)
{
	std::cout << "Start SubRound apelata\n";
	const double timeLimit = 60.0;

	m_timer.start();
	while (m_timer.elapsedSeconds() < timeLimit)
	{
		//check

		if (m_timer.elapsedSeconds() == 30.0)
		{
			m_word.ShowHint();
		}

		else if (m_timer.elapsedSeconds() == 40.0)
		{
			m_word.ShowHint();
		}

		else if (m_timer.elapsedSeconds() == 50.0)
		{
			m_word.ShowHint();
		}


	}
	m_timer.stop();

}
