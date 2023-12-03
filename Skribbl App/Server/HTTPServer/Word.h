#pragma once
#include <string>
#include <iostream>
#include <ctime>


class Word
{

private:
	std::string m_value; 
	std::string m_difficulty; 
	uint16_t m_numberHint;  ///initializare const
	std::string m_valueAux;
	uint16_t m_id;

public:

	Word(const std::string& value, const std::string& difficulty,uint16_t id)
		: m_value(value), m_difficulty(difficulty),m_id(id)
	{
		std::cout << "Constructor apelat\n";
		m_numberHint = m_value.size() / 2;
		for (int i = 0; i < m_value.size(); i++)
		{
			m_valueAux += '_';
		}
	}

	~Word() = default;

	void setValue(const std::string& value);
	void setDifficulty(const std::string& difficulty);

	std::string getDifficulty() const;
	std::string getValue() const;
	uint16_t getNumberHint() ;
	std::string getValueAux();
	uint16_t getId() const;
	

	void PrintPlayerDrawing();
	void PrintPlayerGuessing();

	void ShowHint();
};

