#pragma once
#include <cstdint>
#include <string>
class User
{
public:
	User();
	User(const std::string& username, const std::string& email, const std::string& password, uint16_t personalBest);
	User& operator=(const User& user);
	User(const User& user);

	~User();

	std::string GetUsername();
	std::string GetEmail();
	std::string GetPassword();
	//GetGameHistory()
	uint16_t GetPersonalBest();

	void SetUsername(const std::string& username);
	void SetEmail(const std::string& email);
	void SetPassword(const std::string& password);
	//void SetGameHistory()
	void SetPersonalBest(uint16_t personalBest);

private:
	std::string m_username;
	std::string m_email;
	std::string m_password;
	//gameHistory
	uint16_t m_personalBest;
};

