#include "player.h"

Player::Player() :User()
{
    m_isDrawer = false;
    m_personalScore = 0;
    m_hasGuessed = false;
    m_timeGuessed = 60.0;
}

Player::Player(bool& isDrawing) :User()
{
    m_isDrawer = isDrawing;
    m_personalScore = 0;
    m_hasGuessed = false;
    m_timeGuessed = 60.0;
}

Player::Player(const Player& player)
{
    this->SetEmail(player.GetEmail());
    this->SetUsername(player.GetUsername());
    this->m_isDrawer = player.m_isDrawer;
    this->m_personalScore = player.m_personalScore;
    this->m_hasGuessed = player.m_hasGuessed;
    this->m_timeGuessed = player.m_timeGuessed;
}

Player::Player(bool& hasGuessed, double& timeGuessed,
    bool& isDrawer,  uint16_t& personalScore,  const std::string& email, const std::string& password,
     uint16_t& personalBest)
{
    SetEmail(email);
    SetPassword(password);
    SetPersonalBest(personalBest);
    this->m_isDrawer = isDrawer;
    this->m_personalScore = personalScore;
    this->m_hasGuessed = hasGuessed;
    this->m_timeGuessed = timeGuessed;
}


void Player::SetIsDrawer(bool isDrawing)
{
    m_isDrawer = isDrawing;
}

void Player::SetHasGuessed(bool hasGuessed)
{
    m_hasGuessed = hasGuessed;
}

void Player::SetScore(const double& newscore)
{
    m_personalScore = newscore;
}

//void Player::SetIsDrawer(bool&& isDrawing)
//{
//    m_isDrawer = isDrawing;
//}

bool Player::GetIsDrawer() const
{
    return m_isDrawer;
}

double Player::GetPersonalScore() const
{
    return m_personalScore;
}

void Player::SetTimeGuessed(double time)
{
    m_timeGuessed = time;
}

bool Player::GetHasGuessed() const
{
    return m_hasGuessed;
}

double Player::GetTimeGuessed() const
{
    return m_timeGuessed;
}

Player& Player::operator=(const Player& player)
{
    this->SetEmail(player.GetEmail());
    this->SetUsername(player.GetUsername());
    this->m_isDrawer = player.m_isDrawer;
    this->m_personalScore = player.m_personalScore;
    this->m_hasGuessed = player.m_hasGuessed;
    this->m_timeGuessed = player.m_timeGuessed;
    return *this;
}

bool Player::operator < (const Player& player) const
{
    std::cout << "Compara Player dupa scor apelata";
    return this->m_personalScore < player.m_personalScore;
}

bool Player::operator > (const Player& player) const
{
    std::cout << "Compara Player dupa scor apelata";
    return this->m_personalScore > player.m_personalScore;
}

std::ostream& operator<<(std::ostream& os, Player& player)
{
    os << "username: "<<player.GetUsername() << "\nTime: " << player.GetTimeGuessed()
      << "\nHas Guessed: " << player.GetHasGuessed() << "\nIs Drawer: " << player.GetIsDrawer() << "\nScore: " << player.GetPersonalScore() << "\n";
    return os;
}
