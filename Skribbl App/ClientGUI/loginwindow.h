#pragma once

#include <QWidget>
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include<regex>
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
public slots:
	void onLoginButtonClicked();
	void on_backButton_clicked();

private:
	Ui::LoginWindowClass ui;
	bool validateUserPassword(const std::string& m_password);
	bool validateUsername(const std::string& m_username);
	MainWindow* mainWindow;
};
