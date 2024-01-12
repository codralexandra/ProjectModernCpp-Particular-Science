#pragma once

#include <QWidget>
#include "ui_registerwindow.h"
#include<regex>
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include "thememanager.h";

class RegisterWindow : public QWidget
{
	Q_OBJECT

public:
	RegisterWindow(QWidget *parent = nullptr);
	~RegisterWindow();
	private slots:
		void onRegisterButtonClicked();
		void on_backButton_clicked();
		void handleThemeChanged(const QString& styleSheet);

private:
	Ui::RegisterWindowClass ui;
	bool validateUserPassword(const std::string& m_password);
	bool validateUserEmail(const std::string& m_email);
	bool validateUsername(const std::string& m_username);
	ThemeManager* themeManager;
};
