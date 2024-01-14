#pragma once

#include <QMainWindow>
#include "ui_ScoreWindow.h"
#include "thememanager.h"
#include <cpr/cpr.h>
#include <crow.h>

class ScoreWindow : public QMainWindow
{
	Q_OBJECT

public:
	ScoreWindow(QWidget *parent = nullptr);
	~ScoreWindow();
	void getPlayerScores(crow::json::wvalue jsonPackage);

private slots:
	void on_closeButton_clicked();
	void handleThemeChange(const QString& styleSheet);

private:
	Ui::ScoreWindowClass ui;
	ThemeManager* themeManager;
};