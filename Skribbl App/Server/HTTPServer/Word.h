#pragma once
#include <string>
#include <iostream>
#include <ctime>


class Word
{
public:

	//constructor and destructor
	Word(const uint16_t& id, const std::string& value, const std::string& difficulty);
	Word();
	~Word() = default;
	Word(const Word& word);
	Word(Word&& word) noexcept;

	//setter
	void SetValue(const std::string& value);
	void SetDifficulty(const std::string& difficulty);
	void SetId(const uint16_t& id);

	//getter
	std::string GetDifficulty() const;
	std::string GetValue() const;
	uint16_t GetNumberHint() const;
	std::string GetValueAux() const;
	uint16_t GetId() const;

	//operators
	Word& operator=(const Word& other);
	Word& operator=(Word&& other) noexcept;


	//print
	void PrintPlayerDrawing() const;
	void PrintPlayerGuessing() const;

	void ShowHint();
	void fillvalueAux();


private:
	std::string m_value;
	std::string m_difficulty;
	uint16_t m_numberHint;
	std::string m_valueAux;
	uint16_t m_id;
};

