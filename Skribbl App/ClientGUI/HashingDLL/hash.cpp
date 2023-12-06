#include "hash.h"

void HashMethod::Set(std::string pas)
{
	m_password = pas;
}

std::string HashMethod::Get()
{
	return m_password;
}

void HashMethod::SetHashedPass()
{
	int hash = Hash();
	m_password = std::to_string(hash);
}

int HashMethod::Hash()
{
	int len = m_password.size();
	int h = 0;

	for (int i = 0; i < len; i++)
	{
		h = 33 * h + m_password[i];
	}
	return h;
}
