#include "lobbystate.h"

std::string LobbyStateTypeToString(LobbyState state)
{
	switch (state)
	{
	case LobbyState::Waiting:
	{
		return "Waiting"s;

	}
	case LobbyState::Starting:
		return "Starting"s;
	}
}

LobbyState StringToLobbyState(const std::string& stateString)
{
	if (stateString == "Waiting")
		return LobbyState::Waiting;
	if (stateString == "Starting")
		return LobbyState::Starting;
}
