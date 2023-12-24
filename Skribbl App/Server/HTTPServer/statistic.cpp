#include "statistic.h"

Statistic::Statistic()
{
	//empty
}

Statistic::Statistic(const std::string& username, uint16_t score):m_score(score),m_username(username)
{
}

void Statistic::SetUsername(const std::string& username)
{
	this->m_username = username;
}

void Statistic::SetScore(uint16_t& score)
{
	this->m_score = score;
}

std::string Statistic::GetUsername() const
{
	return m_username;
}

uint16_t Statistic::GetScore() const
{
	return m_score;
}
