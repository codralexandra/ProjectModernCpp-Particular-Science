#include "lobby.h"

Lobby::Lobby(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Lobby::~Lobby()
{}

void Lobby::SetGameID(const uint16_t & id)
{
	m_gameID = id;
	ui.roomCode->setText(QString::number(id));
	update();
}

void Lobby::SetDifficulty(const std::string& diff)
{
	m_difficulty = diff;
}



uint16_t Lobby::GetGameID() const
{
	return m_gameID;
}


std::string Lobby::GetDifficulty() const
{
	return m_difficulty;
}