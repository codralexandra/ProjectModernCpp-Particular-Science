#pragma once

#include <QWidget>
#include "ui_loginwindow.h"
#include "registerwindow.h"

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
public slots:
	void on_registerButton_clicked();

private:
	Ui::LoginWindowClass ui;
	RegisterWindow m_registerWindow;
};
