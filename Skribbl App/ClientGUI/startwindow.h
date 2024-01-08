#pragma once

#include <QMainWindow>
#include "ui_startwindow.h"
#include <cpr/cpr.h>
#include <crow.h>

class StartWindow : public QMainWindow
{
	Q_OBJECT

public:
	StartWindow(QWidget *parent = nullptr);
	~StartWindow();

private:
	void recievePixelFromServer();
	void WordToBeGuessed();
	void updatePlayerRole(bool role);
private:
	Ui::StartWindowClass ui;
	bool isDrawing;
};
