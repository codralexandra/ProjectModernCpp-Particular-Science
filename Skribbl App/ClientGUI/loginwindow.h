#pragma once

#include <QWidget>
#include "ui_loginwindow.h"

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
public slots:
	void on_backButton_clicked();

private:
	Ui::LoginWindowClass ui;
};
