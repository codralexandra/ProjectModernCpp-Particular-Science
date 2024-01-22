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
int HexStringToColorPosition(const std::string& hexString) {
	Color color;

	if (hexString == "#000000") color = Color::Black;
	else if (hexString == "#ff0000") color = Color::Red;
	else if (hexString == "#3498db") color = Color::Blue;
	else if (hexString == "#008000") color = Color::Green;
	else if (hexString == "#ffff00") color = Color::Yellow;
	else if (hexString == "#ffc0cb") color = Color::Pink;
	else if (hexString == "#800080") color = Color::Purple;
	else if (hexString == "#964b00") color = Color::Brown;
	else color = Color::Black; // Default or error case

	return static_cast<int>(color);
}

std::string ColorToHexString(int color) {
	switch (color) {
	case 0: return "#000000"; // Black
	case 1: return "#ff0000"; // Red
	case 2: return "#3498db"; // Blue
	case 3: return "#008000"; // Green
	case 4: return "#ffff00"; // Yellow
	case 5: return "#ffc0cb"; // Pink
	case 6: return "#800080"; // Purple
	case 7: return "#964b00"; // Brown
	default: return "#000000"; // Default or error case
	}
}