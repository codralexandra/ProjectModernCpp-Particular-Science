#pragma once

#include <QMainWindow>
#include "ui_ScoreWindow.h"
#include "thememanager.h"

class ScoreWindow : public QMainWindow
{
	Q_OBJECT

public:
	ScoreWindow(QWidget *parent = nullptr);
	~ScoreWindow();
	void getPlayerScores();
private slots:
	void on_closeButton_clicked();
	void handleThemeChange(const QString& styleSheet);

private:
	Ui::ScoreWindowClass ui;
	ThemeManager* themeManager;
};
