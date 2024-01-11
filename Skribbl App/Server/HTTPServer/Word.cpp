#include "Word.h"
#include <iostream>
#include <ctime>

Word::Word(const uint16_t& id, const std::string& value, const std::string& difficulty)
	: m_id(id), m_value(value), m_difficulty(difficulty)
{
	m_numberHint = m_value.size() / 2;
	for (int i = 0; i < m_value.size(); i++)
	{
		if (m_value[i] == '-')
			m_valueAux += ' ';
		else
			m_valueAux += '_';
	}
}
Word::Word()
{
	m_value = "";
	m_difficulty = "";
	m_numberHint = 0;
	m_valueAux = "";
	m_id = -1;
}
Word::Word(const Word& word)
{
	this->m_id = word.m_id;
	this->m_numberHint = word.m_numberHint;
	this->m_difficulty = word.m_difficulty;
	this->m_value = word.m_value;
	this->m_valueAux = word.m_valueAux;
}
Word::Word(Word&& word) noexcept: m_id(word.m_id), m_value(word.m_value), m_difficulty(word.m_difficulty)
{
	word.m_difficulty.clear();
	word.m_id = -1;
	word.m_value.clear();
}
void Word::SetValue(const std::string& value)
{
	this->m_value = value;
}

void Word::SetDifficulty(const std::string& difficulty)
{
	this->m_difficulty = difficulty;
}

std::string Word::GetDifficulty() const
{
	return m_difficulty;
}

std::string Word::GetValue() const
{
	return m_value;
}

uint16_t Word::GetNumberHint() const
{
	return m_numberHint;
}

std::string Word::GetValueAux() const
{
	return m_valueAux;
}

uint16_t Word::GetId() const
{
	return m_id;
}

Word& Word::operator=(const Word& other)
{
	if (this != &other)
	{
		this->m_id = other.m_id;
		this->m_difficulty = other.m_difficulty;
		this->m_value.clear();
		m_valueAux.clear();
		m_value = other.m_value;
		m_valueAux = other.m_valueAux;
		m_numberHint = other.m_numberHint;
	}

	return *this;
}

Word& Word::operator=(Word&& other) noexcept
{
	if (this != &other)
	{
		this->m_id = other.m_id;
		this->m_difficulty = other.m_difficulty;
		this->m_value.clear();
		m_valueAux.clear();
		m_value = other.m_value;
		m_valueAux = other.m_valueAux;
		m_numberHint = other.m_numberHint;
		other.m_id = -1;
		other.m_difficulty.clear();
		other.m_value.clear();
		other.m_valueAux.clear();
		other.m_numberHint = 0;
	}

	return *this;
}

void Word::SetId(const uint16_t& id)
{
	m_id = id;
}

void Word::PrintPlayerDrawing() const
{
	std::cout << "The word is: " << m_value << std::endl;
}

void Word::PrintPlayerGuessing() const
{
	std::cout << "The word is: " << m_valueAux << std::endl;
}

void Word::ShowHint()
{
	std::cout << "ShowHint apelata\n";
	if (m_numberHint > 0)
	{
		std::cout << "Take a hint\n";
		srand(0);
		bool ok = false;
		int randomPosition = rand() % m_valueAux.size();
		while (m_valueAux[randomPosition] != '_')
		{
			randomPosition = rand() % m_valueAux.size();
		}
		std::cout << "This is the hint\n";
		std::cout << randomPosition << " " << m_value[randomPosition] << std::endl;
		m_valueAux[randomPosition] = m_value[randomPosition];
		m_numberHint -= 1;
	}
	std::cout << "This is the word with hints: " << m_valueAux << std::endl;
}
