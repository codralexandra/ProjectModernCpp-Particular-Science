#include "Word.h"

void Word::setValue(const std::string& value)
{
	this->m_value = value;
}

void Word::setDifficulty(const std::string& difficulty)
{
	this->m_difficulty = difficulty;
}

std::string Word::getDifficulty()
{
	return m_difficulty;
}

std::string Word::getValue()
{
	return m_value;
}

uint16_t Word::getNumberHint()
{
	return m_numberHint;
}
