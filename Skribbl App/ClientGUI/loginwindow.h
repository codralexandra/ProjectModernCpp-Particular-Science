#pragma once

#include <QWidget>
#include "ui_loginwindow.h"
#include <cpr/cpr.h>
#include <crow.h>

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
public slots:
	void on_loginButton_clicked();
	void on_backButton_clicked();

private:
	Ui::LoginWindowClass ui;
};
