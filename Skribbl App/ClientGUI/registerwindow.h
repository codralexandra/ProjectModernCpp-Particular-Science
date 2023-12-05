#pragma once

#include <QWidget>
#include "ui_registerwindow.h"
#include<regex>
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
	bool validateUserPassword(QString m_password);
};
