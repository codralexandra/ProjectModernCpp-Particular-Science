#pragma once
#include <string>
#include <cstdint>
using namespace std::string_literals;

enum class Color : uint8_t
{
	Black,
	Red,
	Blue,
	Green,
	Yellow,
	Pink,
	Purple,
	Brown
};

std::string DifficultyTypeToString(const Color& dif);
Color StringToColorType(const std::string& colorString);
