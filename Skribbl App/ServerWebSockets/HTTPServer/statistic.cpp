#include "statistic.h"
using namespace Scribble;
Statistic::Statistic()
{
	//empty
}

Statistic::Statistic(const std::string& username, uint16_t& score):m_score(score),m_username(username),m_id(-1)
{
	//empty
}

Scribble::Statistic::Statistic(const Statistic& other):m_username(other.m_username), m_score(other.m_score),m_id(-1)
{
	//empty
}

Scribble::Statistic::Statistic(Statistic&& other) noexcept
{
	m_username = std::move(other.m_username);
	m_score = std::move(other.m_score);
	m_id = other.m_id;

}

Statistic& Scribble::Statistic::operator=(const Statistic& other)
{
	if (this != &other) {
		
		m_username = other.m_username;
		m_score = other.m_score;
		m_id = other.m_id;

	}
	return *this;
}

Statistic& Scribble::Statistic::operator=(Statistic&& other) noexcept
{
	if (this != &other) {
		
		m_username = std::move(other.m_username);
		m_score = std::move(other.m_score);

	}
	return *this;
}

void Statistic::SetUsername(const std::string& username)
{
	this->m_username = username;
}

void Statistic::SetScore(uint16_t& score)
{
	this->m_score = score;
}

void Scribble::Statistic::SetId(uint16_t id)
{
	m_id = id;
}

std::string Statistic::GetUsername() const
{
	return m_username;
}

uint16_t Statistic::GetScore() const
{
	return m_score;
}

uint16_t Scribble::Statistic::GetId() const
{
	return m_id;
}
