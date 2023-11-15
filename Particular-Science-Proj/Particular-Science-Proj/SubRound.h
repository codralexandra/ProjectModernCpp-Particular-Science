#pragma once
#include <string>
#include "Round.h"
#include <iostream>

class SubRound:public Round
{
public:
	SubRound();
	void SetWord(const std::string& cuv);
	const std::string GetWord()const;
	void StartSubRound();

private:
	std::string word;
	//Qtimer time;
};

