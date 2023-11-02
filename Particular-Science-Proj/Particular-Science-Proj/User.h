#pragma once
#include <cstdint>
#include <string>
#include <queue>
#include<iostream>

class User
{
public:
	User();
	User(const std::string& email, const std::string& password, const std::queue<std::pair<uint16_t, std::string>> gameHistory, uint16_t personalBest);
	User& operator=(const User& user);
	User(const User& user);
	friend std::ostream& operator<<(std::ostream& ostream, const User& user);
	bool validateUserEmail();
	bool validateUserPassword();
	~User();

	std::string GetEmail();
	std::string GetPassword();
	std::queue<std::pair<uint16_t, std::string>> GetGameHistory();
	uint16_t GetPersonalBest();

	void SetEmail(const std::string& email);
	void SetPassword(const std::string& password);
	void SetGameHistory(const std::queue<std::pair<uint16_t, std::string>> gameHistory);
	void SetPersonalBest(uint16_t personalBest);

	void AddGameToGameHistory(std::pair<uint16_t, std::string> game);

private:
	std::string m_email;
	std::string m_password;
	std::queue<std::pair<uint16_t, std::string>> m_gameHistory;
	uint16_t m_personalBest;
};

