#include "User.h"

User::User(): m_email(""), m_password(""), m_gameHistory(), m_personalBest(0)
{

}

User::User(const std::string& email, const std::string& password, const std::queue<std::pair<uint16_t, std::string>> gameHistory, uint16_t personalBest):
	m_email(email), m_password(password), m_gameHistory(gameHistory), m_personalBest(personalBest)
{

}

User& User::operator=(const User& user)
{
	m_email = user.m_email;
	m_password = user.m_password;
	m_personalBest = user.m_personalBest;
	return *this;
}

User::User(const User& user)
{
	m_email = user.m_email;
	m_password = user.m_password;
	m_personalBest = user.m_personalBest;
}

User::~User()
{
}

std::string User::GetEmail()
{
	return m_email;
}

std::string User::GetPassword()
{
	return m_password;
}

uint16_t User::GetPersonalBest()
{
	return m_personalBest;
}

void User::SetEmail(const std::string& email)
{
	m_email = email;
}

void User::SetPassword(const std::string& password)
{
	m_password = password;
}

void User::SetPersonalBest(uint16_t personalBest)
{
	m_personalBest = personalBest;
}

