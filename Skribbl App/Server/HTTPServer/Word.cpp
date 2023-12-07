#include "Word.h"
#include <iostream>
#include <ctime>



Word::Word(const uint16_t& id,const std::string& value, const std::string& difficulty)
	: m_id(id),m_value(value), m_difficulty(difficulty)
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
	 m_difficulty="";
	 m_numberHint = 0;  ///initializare const
	 m_valueAux= "";
	 m_id = -1;
}
void Word::setValue(const std::string& value)
{
	this->m_value = value;
}

void Word::setDifficulty(const std::string& difficulty)
{
	this->m_difficulty = difficulty;
}

std::string Word::getDifficulty() const
{
	return m_difficulty;
}

std::string Word::getValue() const
{
	return m_value;
}

uint16_t Word::getNumberHint() const
{
	return m_numberHint;
}

std::string Word::getValueAux() const 
{
	return m_valueAux;
}

uint16_t Word::getId() const
{
    return m_id;
}

void Word::SetId(const uint16_t& id)
{
	m_id = id;
}

void Word::PrintPlayerDrawing()
{
	std::cout << "The word is: " << m_value << std::endl;
}

void Word::PrintPlayerGuessing()
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
        int randomPosition= rand() % m_valueAux.size();
        while (m_valueAux[randomPosition] != '_')
        {
            randomPosition = rand() % m_valueAux.size();
        }
        std::cout << "This is the hint\n";
        std::cout << randomPosition << " " << m_value[randomPosition]<<std::endl;
        m_valueAux[randomPosition] = m_value[randomPosition];
        m_numberHint -= 1;
    }
    std::cout << "This is the word with hints: " << m_valueAux << std::endl;
}
