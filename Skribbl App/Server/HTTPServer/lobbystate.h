#pragma once

#include<string>

using namespace std::string_literals;

enum class LobbyState
{
	Waiting,
	Starting
};

std::string LobbyStateTypeToString(LobbyState state);
LobbyState StringToLobbyState(const std::string& stateString);
