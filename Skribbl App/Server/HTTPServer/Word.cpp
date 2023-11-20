#include "Word.h"
#include <iostream>
#include <ctime>

void Word::setValue(const std::string& value)
{
	this->m_value = value;
}

void Word::setDifficulty(const std::string& difficulty)
{
	this->m_difficulty = difficulty;
}

std::string Word::getDifficulty()
{
	return m_difficulty;
}

std::string Word::getValue()
{
	return m_value;
}

uint16_t Word::getNumberHint()
{
	return m_numberHint;
}

std::string Word::getValueAux()
{
	return m_valueAux;
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
