#pragma once

#include <QWidget>
#include "ui_joingame.h"
#include <string>
#include "lobby.h"

class JoinGame : public QWidget
{
	Q_OBJECT

public:
	JoinGame(QWidget *parent = nullptr);
	~JoinGame();
	void SetUsername(const std::string& name);
	std::string GetUsername() const;

private slots:
	void on_joinGameButton_clicked();

private:
	Ui::JoinGameClass ui;
	std::string m_username;
};
