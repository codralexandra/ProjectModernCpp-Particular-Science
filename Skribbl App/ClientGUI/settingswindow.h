#pragma once

#include <QWidget>
#include "ui_settingswindow.h"
#include "soundmanager.h"

class SettingsWindow : public QWidget
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = nullptr);
	~SettingsWindow();

public slots:
	void setSoundVolume(uint32_t volume);

private:
	Ui::SettingsWindowClass ui;
	SoundManager* soundManager;
};
