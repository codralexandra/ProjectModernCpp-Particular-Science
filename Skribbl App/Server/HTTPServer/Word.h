#pragma once
#include <string>
#include <iostream>
class Word
{

private:
	std::string m_value; 
	std::string m_difficulty; 
	uint16_t m_numberHint;  ///initializare const
	std::string m_valueAux;
public:

	Word(const std::string& value, const std::string& difficulty, std::string& valueAux)
		: m_value(value), m_difficulty(difficulty)
	{
		m_numberHint = m_value.size() / 2;
		for (int i = 0; i < m_value.size(); i++)
		{
			valueAux += '_';
		}
	}

	~Word() = default;

	void setValue(const std::string& value);
	void setDifficulty(const std::string& difficulty);

	std::string getDifficulty();
	std::string getValue();
	uint16_t getNumberHint();
	std::string getValueAux();

	void PrintPlayerDrawing();
	void PrintPlayerGuessing();
};

