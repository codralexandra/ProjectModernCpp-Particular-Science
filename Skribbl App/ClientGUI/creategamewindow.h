#pragma once

#include <QWidget>
#include "ui_creategamewindow.h"

class CreateGameWindow : public QWidget
{
	Q_OBJECT

public:
	CreateGameWindow(QWidget *parent = nullptr);
	~CreateGameWindow();

private:
	Ui::CreateGameWindowClass ui;
};
