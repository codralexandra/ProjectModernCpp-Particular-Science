#include "Color.h"

std::string DifficultyTypeToString(const Color& dif)
{
	switch (dif)
	{
	case Color::Black:
		return "Black"s;
	case Color::Blue:
		return "Blue"s;
	case Color::Brown:
		return "Brown"s;
	case Color::Red:
		return "Red"s;
	case Color::Green:
		return "Green"s;
	case Color::Yellow:
		return"Yellow"s;
	case Color::Pink:
		return"Pink"s;
	case Color::Purple:
		return "Purple"s;

	}
}
Color StringToColorType(const std::string& colorString) {
	if (colorString == "black") {
		return Color::Black;
	}
	else if (colorString == "blue") {
		return Color::Blue;
	}
	else if (colorString == "red") {
		return Color::Red;
	}
	else if (colorString == "yellow") {
		return Color::Yellow;
	}
	else if (colorString == "pink") {
		return Color::Pink;
	}
	else if (colorString == "purple") {
		return Color::Purple;
	}
	else if (colorString == "green") {
		return Color::Green;
	}
	else if (colorString == "brown") {
		return Color::Brown;
	}
	return Color::Black;
}