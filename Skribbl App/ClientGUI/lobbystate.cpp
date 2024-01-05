#include "lobbystate.h"

std::string LobbyStateToString(LobbyState state)
{
    switch (state)
    {
    case LobbyState::Waiting:
        return "Waiting"s;
    case LobbyState::Starting:
        return "Starting"s;
    }
}

LobbyState StringToLobbyState(const std::string& state)
{
    if (state == "Waiting")
    {
        return LobbyState::Waiting;
    }
    if (state == "Starting")
    {
        return LobbyState::Starting;
    }
    return LobbyState::Waiting;
}
