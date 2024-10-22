#pragma once

#include <QWidget>
#include "ui_profilewindow.h"
#include <QScrollArea>
#include <cpr/cpr.h>
#include <crow.h>
#include "thememanager.h";

class profileWindow : public QWidget
{
	Q_OBJECT

public:
	profileWindow(QWidget *parent = nullptr);
	~profileWindow();
	void setUsername(std::string username);
	
public slots:
	void on_refreshHistoryButton_clicked();

private slots:
	void handleThemeChanged(const QString& styleSheet);

private:
	Ui::profileWindowClass ui;
	std::string m_username;
	float m_averageScore;
	ThemeManager* themeManager;
};
