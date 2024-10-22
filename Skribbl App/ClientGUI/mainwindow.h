#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "creategamewindow.h"
#include "profilewindow.h";
#include "thememanager.h";

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void SetUsername(const std::string& username);
	std::string GetUsername()const;


private slots:
	void on_joinButton_clicked();
	void on_createButton_clicked();
	void on_profileButton_clicked();
	void handleThemeChanged(const QString& styleSheet);

private:
	Ui::MainWindowClass ui;
	CreateGameWindow* createGameWindow;
	std::string m_username;
	profileWindow profileWindow;
	ThemeManager* themeManager;
};
