#pragma once

#include <QWidget>
#include "ui_creategamewindow.h"
#include "lobby.h";
#include "thememanager.h"

class CreateGameWindow : public QWidget
{
	Q_OBJECT

public:
	CreateGameWindow(QWidget *parent = nullptr);
	~CreateGameWindow();
	void SetUsername(const std::string& username);
	std::string GetUsername()const;

private slots:
	void on_createLobbyButton_clicked();
	void handleThemeChanged(const QString& styleSheet);

private:
	Ui::CreateGameWindowClass ui;
	Lobby* lobby;
	std::string m_username;
	ThemeManager* themeManager;
};
