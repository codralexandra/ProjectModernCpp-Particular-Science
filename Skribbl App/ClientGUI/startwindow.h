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
	void SetUsername(const std::string& name);
	std::string GetUsername() const;
	void connectionToRoute();
	void WordToBeGuessed();
	void recievePixelFromServer();
	void updatePlayerRole(crow::json::rvalue jsonBody);



private:
	Ui::StartWindowClass ui;
	bool isDrawing;
	std::string m_username;
};
