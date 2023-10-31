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
	m_gameHistory = user.m_gameHistory;
	m_personalBest = user.m_personalBest;
	return *this;
}

User::User(const User& user)
{
	m_email = user.m_email;
	m_password = user.m_password;
	m_gameHistory = user.m_gameHistory;
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

std::queue<std::pair<uint16_t, std::string>> User::GetGameHistory()
{
	return m_gameHistory;
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

void User::SetGameHistory(const std::queue<std::pair<uint16_t, std::string>> gameHistory)
{
	m_gameHistory = gameHistory;
}

void User::SetPersonalBest(uint16_t personalBest)
{
	m_personalBest = personalBest;
}

void User::AddGameToGameHistory(std::pair<uint16_t, std::string> game)
{
	if (m_gameHistory.size() >= 5)
	{
		m_gameHistory.pop();
		m_gameHistory.push(game);
	}
	else
	{
		m_gameHistory.push(game);
	}
}

std::ostream& operator<<(std::ostream& ostream, const User& user)
{
	std::queue<std::pair<uint16_t, std::string>> copyGameHistory = user.m_gameHistory;
	ostream <<"Email: " << user.m_email <<"\n" 
		<< "Password: " << user.m_password << "\n"
		<< "Game history: \n";
	while (!copyGameHistory.empty())
	{
		ostream << copyGameHistory.front().first << ", " << copyGameHistory.front().first << " ";
		copyGameHistory.pop();
	}
	ostream << "Personal best: " << user.m_personalBest << "\n";
	return ostream;
}
