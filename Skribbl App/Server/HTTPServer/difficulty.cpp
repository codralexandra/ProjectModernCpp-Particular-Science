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