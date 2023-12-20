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

	Word(const uint16_t& id, const std::string& value, const std::string& difficulty);
	Word();
	~Word() = default;

	void setValue(const std::string& value);
	void setDifficulty(const std::string& difficulty);
	void SetId(const uint16_t& id);

	std::string getDifficulty() const;
	std::string getValue() const;
	uint16_t getNumberHint() const;
	std::string getValueAux() const;
	uint16_t getId() const;


	void PrintPlayerDrawing() const;
	void PrintPlayerGuessing() const;

	void ShowHint();

};

