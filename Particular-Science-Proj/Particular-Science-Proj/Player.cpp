#include "Player.h"

Player::Player()
{
    m_isDrawing = false;
    m_hasTopScore = false;
    m_personalScore = 0;
    m_position = 1;
}

Player::Player(bool isDrawing)
{
    m_isDrawing = isDrawing;
    m_hasTopScore = false;
    m_personalScore = 0;
    m_position = 1;
}

Player::Player(const Player& player)
{
    this->m_isDrawing = player.m_isDrawing;
    this->m_hasTopScore = player.m_hasTopScore;
    this->m_personalScore = player.m_personalScore;
    this->m_position = player.m_position;
}

void Player::SetIsDrawing()
{
    m_isDrawing = true;
}

void Player::UpdateScore(int16_t newscore)
{
    m_personalScore = newscore;
}

void Player::UpdatePosition(uint16_t position)
{
    m_position = position;
}

bool Player::GetIsDrawing()
{
    return m_isDrawing;
}

int16_t Player::GetPersonalScore()
{
    return m_personalScore;
}

bool Player::GetHasTopScore()
{
    return m_hasTopScore;
}

uint16_t Player::GetPosition()
{
    return m_position;
}
