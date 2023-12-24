#pragma once
#include <string>
class Statistic
{
public:
	Statistic();
	Statistic(const std::string& username, uint16_t score);
private:
	std::string m_username;
	uint16_t m_score;

};

