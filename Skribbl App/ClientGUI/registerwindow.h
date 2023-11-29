#pragma once

#include <QWidget>
#include "ui_registerwindow.h"

class RegisterWindow : public QWidget
{
	Q_OBJECT

public:
	RegisterWindow(QWidget *parent = nullptr);
	~RegisterWindow();

private:
	Ui::RegisterWindowClass ui;
};
