#include "Player.h"

Player::Player()
{
    m_nickname = " ";
    m_isDrawing = false;
    m_hasTopScore = false;
    m_personalScore = 0;
    m_position = 1;
    m_hasDrawn = false;
    m_hasGuessed = false;
    m_timeGuessed = 60;
}

Player::Player(bool isDrawing)
{
    m_nickname = " ";
    m_isDrawing = isDrawing;
    m_hasTopScore = false;
    m_personalScore = 0;
    m_position = 1;
    m_hasDrawn = false;
    m_hasGuessed = false;
    m_timeGuessed = false;
}

Player::Player(const Player& player)
{
    this->m_nickname = player.m_nickname;
    this->m_isDrawing = player.m_isDrawing;
    this->m_hasTopScore = player.m_hasTopScore;
    this->m_personalScore = player.m_personalScore;
    this->m_position = player.m_position;
    this->m_hasDrawn = player.m_hasDrawn;
    this->m_hasGuessed = player.m_hasGuessed;
    this->m_timeGuessed = player.m_timeGuessed;
}




void Player::SetNickname(std::string nickname)
{
    m_nickname = nickname;
}

void Player::SetIsDrawing(bool isDrawing)
{
    m_isDrawing = isDrawing;
}

void Player::SetHasGuessed(bool hasGuessed)
{
    m_hasGuessed = hasGuessed;
}

void Player::SetHasDrawn(bool hasDrawn)
{
    m_hasDrawn = hasDrawn;
}

void Player::UpdateScore(int16_t newscore)
{
    m_personalScore = newscore;
}

void Player::UpdatePosition(uint16_t position)
{
    m_position = position;
}





std::string Player::GetNickname()
{
    return m_nickname;
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

bool Player::GetHasGuessed()
{
    return m_hasGuessed;
}

bool Player::GetHasDrawn()
{
    return m_hasDrawn;
}

uint16_t Player::GetTimeGuessed()
{
    return m_timeGuessed;
}





Player& Player::operator=(const Player& player)
{
    this->m_nickname = player.m_nickname;
    this->m_isDrawing = player.m_isDrawing;
    this->m_hasTopScore = player.m_hasTopScore;
    this->m_personalScore = player.m_personalScore;
    this->m_position = player.m_position;
}

bool Player::operator < (const Player& player) const
{
    return this->m_personalScore < player.m_personalScore;
}

bool Player::operator > (const Player& player) const
{
    return this->m_personalScore > player.m_personalScore;
}
