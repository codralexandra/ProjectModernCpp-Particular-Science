module;
export module user;
#include <cstdint>;
#include <string>;
#include <queue>;
#include<iostream>;

namespace Scribble
{
	export class User
	{
	private:
		std::string m_email;
		std::string m_password;
		std::queue<std::pair<uint16_t, std::string>> m_gameHistory;
		uint16_t m_personalBest;
	};
}

