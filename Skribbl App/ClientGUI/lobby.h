#pragma once

#include <QWidget>
#include "ui_lobby.h"
#include <string>

class Lobby : public QWidget
{
	Q_OBJECT

public:
	Lobby(QWidget *parent = nullptr);
	~Lobby();
	void SetGameID(const uint16_t& id);
	void SetDifficulty(const std::string& diff);

	uint16_t GetGameID() const;
	std::string GetDifficulty()const;

private:
	Ui::LobbyClass ui;
	uint16_t m_gameID;
	std::string m_difficulty;
};