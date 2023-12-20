#pragma once

#include <QMainWindow>
#include "ui_startwindow.h"

class StartWindow : public QMainWindow
{
	Q_OBJECT

public:
	StartWindow(QWidget *parent = nullptr);
	~StartWindow();

private:
	void recievePixelFromServer();

private:
	Ui::StartWindowClass ui;
};
