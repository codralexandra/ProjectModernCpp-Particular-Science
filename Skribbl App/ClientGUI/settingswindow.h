#pragma once

#include <QWidget>
#include "ui_settingswindow.h"
#include "soundmanager.h"
#include "thememanager.h"

class SettingsWindow : public QWidget
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = nullptr);
	~SettingsWindow();

public slots:
	void setSoundVolume(uint32_t volume);
	void on_darkThemeButton_clicked();
	void on_lightThemeButton_clicked();
	void on_colorThemeButton_clicked();
private slots:
	void handleThemeChanged(const QString& styleSheet);

private:
	Ui::SettingsWindowClass ui;
	SoundManager* soundManager;
	ThemeManager* themeManager;
};
