#pragma once
#include <string>
#include <cstdint>
using namespace std::string_literals;

enum class Difficulty : uint8_t
{
	Easy,
	Medium,
	Hard
};

std::string DifficultyTypeToString(Difficulty dif);
Difficulty StringToDifficultyType(const std::string& difficultyString);