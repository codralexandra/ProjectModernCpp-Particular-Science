#include "Player.h"

void Player::SetIsDrawing()
{
    m_isDrawing = true;
}

void Player::UpdateScore(int16_t newscore)
{
    m_personalScore = newscore;
}

bool Player::GetIsDrawing()
{
    return m_isDrawing;
}

int16_t Player::GetPersonalScore()
{
    return m_personalScore;
}

std::string Player::GetPlayerUsername()
{
    return User::GetUsername();
}

bool Player::GetHasTopScore()
{
    return m_hasTopScore;
}
