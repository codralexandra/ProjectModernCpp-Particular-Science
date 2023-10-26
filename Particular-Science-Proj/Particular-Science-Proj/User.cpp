#include "User.h"

User::User(): m_username(""), m_email(""), m_password(""), m_personalBest(0)
{

}

User::User(const std::string& username, const std::string& email, const std::string& password, uint16_t personalBest): 
	m_username(username), m_email(email), m_password(password), m_personalBest(personalBest)
{
}

User& User::operator=(const User& user)
{
	m_username = user.m_username;
	m_email = user.m_email;
	m_password = user.m_password;
	m_personalBest = user.m_personalBest;
}

User::User(const User& user)
{
	m_username = user.m_username;
	m_email = user.m_email;
	m_password = user.m_password;
	m_personalBest = user.m_personalBest;
}

User::~User()
{
}

std::string User::GetUsername()
{
	return m_username;
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

void User::SetUsername(const std::string& username)
{
	m_username = username;
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

