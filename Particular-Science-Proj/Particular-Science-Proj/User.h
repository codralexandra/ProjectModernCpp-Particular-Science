#pragma once
#include <cstdint>
#include <string>
class User
{
private:
	std::string m_username;
	std::string m_email;
	std::string m_password;
	//istoric jocuri
	uint16_t m_personal_best;
};

