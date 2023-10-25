#include "Score.h"

Score::Score(): m_timp(0),m_dificultate("usor")
{
	
}

Score::Score(uint16_t timp, const std::string& dificultate):m_timp(timp), m_dificultate(dificultate)
{
}

Score::Score(const Score& s)
{
	this->m_timp = s.m_timp;
	this->m_dificultate = s.m_dificultate;
}

Score& Score::operator=(const Score& s)
{
	this->m_timp = s.m_timp;
	this->m_dificultate = s.m_dificultate;
}

void Score::SetTime(uint16_t timp)
{
	this->m_timp = timp;
}

void Score::SetDificulty(const std::string& dificultate)
{
	this->m_dificultate = dificultate;
}

uint16_t Score::GetTime()
{
	return this->m_timp;
}

std::string Score::GetDificulty()
{
	return this->m_dificultate;
}

