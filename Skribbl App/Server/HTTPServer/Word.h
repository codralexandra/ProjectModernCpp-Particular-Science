#pragma once
#include <string>
class Word
{

private:
	std::string m_value;
	std::string m_difficulty;
	uint16_t m_numberHint;  ///initializare const
public:

	Word(const std::string& m_value, const std::string& m_difficulty)
		: m_value(m_value), m_difficulty(m_difficulty)
	{
		m_numberHint = m_value.size() / 2;
	}

	~Word() = default;

	void setValue(const std::string& value);
	void setDifficulty(const std::string& difficulty);

};

