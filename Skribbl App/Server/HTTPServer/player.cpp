module player;
using Scribble::Player;


Player::Player() :User()
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

Player::Player(bool isDrawing) :User()
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
    //SetEmail(player.get...)  nu merge player e const help
    this->m_nickname = player.m_nickname;
    this->m_isDrawing = player.m_isDrawing;
    this->m_hasTopScore = player.m_hasTopScore;
    this->m_personalScore = player.m_personalScore;
    this->m_position = player.m_position;
    this->m_hasDrawn = player.m_hasDrawn;
    this->m_hasGuessed = player.m_hasGuessed;
    this->m_timeGuessed = player.m_timeGuessed;
}

Player::Player(bool hasGuessed, bool hasDrawn, uint16_t timeGuessed, std::string nickname,
    bool isDrawing, bool hasTopScore, int16_t personalScore, uint16_t position, const std::string& email, const std::string& password,
    const std::queue<std::pair<uint16_t, std::string>> gameHistory, uint16_t personalBest)
{
    SetEmail(email);
    SetGameHistory(gameHistory);
    SetPassword(password);
    SetPersonalBest(personalBest);
    this->m_nickname = nickname;
    this->m_isDrawing = isDrawing;
    this->m_hasTopScore = hasTopScore;
    this->m_personalScore = personalScore;
    this->m_position = position;
    this->m_hasDrawn = hasDrawn;
    this->m_hasGuessed = hasGuessed;
    this->m_timeGuessed = timeGuessed;
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

void Player::SetScore(int16_t newscore)
{
    m_personalScore = newscore;
}

void Player::SetPosition(uint16_t position)
{
    m_position = position;
}

void Scribble::Player::SetHasTopScore(bool topScore)
{
    m_hasTopScore = topScore;
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
    this->m_hasDrawn = player.m_hasDrawn;
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

std::ostream& Scribble::operator<<(std::ostream& os, Player& player)
{
    os << "Nickname: " << player.GetNickname() << "\nPosition: " << player.GetPosition() << "\nTime: " << player.GetTimeGuessed()
        << "\nLeader: " << player.GetHasTopScore() << "\nHas Guessed: " << player.GetHasGuessed() << "\nHas Drawn: "
        << player.GetHasDrawn() << "\nIs Drawing: " << player.GetIsDrawing() << "\nScore: " << player.GetPersonalScore() << "\n";
    return os;
}
