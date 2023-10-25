#include "Score.h"

Score::Score(): m_timp(0),m_dificultate("usor")
{
	
}

Score::Score(uint16_t timp, const std::string& dificultate):m_timp(timp), m_dificultate(dificultate)
{
}

void Score::SetTimp(uint16_t timp)
{
	this->m_timp = timp;
}

void Score::SetDificultate(const std::string& dificultate)
{
	this->m_dificultate = dificultate;
}

