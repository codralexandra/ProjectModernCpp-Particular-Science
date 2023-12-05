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
class RegisterWindow : public QWidget
{
	Q_OBJECT

public:
	RegisterWindow(QWidget *parent = nullptr);
	~RegisterWindow();
	private slots:
		void onRegisterButtonClicked();

private:
	Ui::RegisterWindowClass ui;
	bool validateUserPassword(const std::string& m_password);
	bool validateUserEmail(const std::string& m_email);
	std::string QStringConversion(QString string);
};
