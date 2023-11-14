#pragma once
#include <string>
#include "Round.h"
#include <iostream>

class SubRound:public Round
{
	SubRound();
	void SetWord(const std::string& cuv);
	const std::string GetWord()const;
	void StartSubRound();
	void PrintWordToGuess();

private:
	std::string word;
	//Qtimer time;
};

