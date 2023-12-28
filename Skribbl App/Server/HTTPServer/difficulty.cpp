#include "difficulty.h"

std::string DifficultyTypeToString(Difficulty dif)
{
	switch (dif)
	{
	case Difficulty::Easy:
		return "Easy"s;
	case Difficulty::Medium:
		return "Medium"s;
	case Difficulty::Hard:
		return "Hard"s;
	}
}
Difficulty StringToDifficultyType(const std::string& difficultyString) {
	if (difficultyString == "Easy") {
		return Difficulty::Easy;
	}
	else if (difficultyString == "Medium") {
		return Difficulty::Medium;
	}
	else if (difficultyString == "Hard") {
		return Difficulty::Hard;
	}
	return Difficulty::Easy;
}