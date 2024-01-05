#pragma once
#include <string>

using namespace std::string_literals;

enum class LobbyState : uint8_t
{
	Waiting,
	Starting
};

std::string LobbyStateToString(LobbyState state);
LobbyState StringToLobbyState(const std::string& state);