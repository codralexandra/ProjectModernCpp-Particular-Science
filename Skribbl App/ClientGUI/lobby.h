#pragma once

#include <QWidget>
#include "ui_lobby.h"
#include <string>
#include <cpr/cpr.h>
#include <crow.h>
#include "lobbystate.h"
#include "startwindow.h"

class Lobby : public QWidget
{
	Q_OBJECT

public:
	Lobby(QWidget *parent = nullptr);
	~Lobby();
	void SetGameID(const uint16_t& id);
	void SetDifficulty(const std::string& diff);
	void SetGameMaster(const bool& gameMaster);

	uint16_t GetGameID() const;
	std::string GetDifficulty()const;
	bool GetGameMaster() const;
	
private slots:
	void on_startGameButton_clicked();

private:
	Ui::LobbyClass ui;
	uint16_t m_gameID;
	std::string m_difficulty;
	LobbyState m_state;
	StartWindow gameWindow;
	bool m_gameMaster;
};
