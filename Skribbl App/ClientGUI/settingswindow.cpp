#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
	: QWidget(parent), soundManager(new SoundManager(this))
{
	ui.setupUi(this);
	connect(ui.songVolume, &QSlider::valueChanged, this, &SettingsWindow::setSoundVolume);
	ui.volumeValue->setText("Volume: " + QString::number(ui.songVolume->value()));
}

SettingsWindow::~SettingsWindow()
{}

void SettingsWindow::setSoundVolume(uint32_t volume)
{
	soundManager->setVolume(volume);
	ui.volumeValue->setText("Volume: " + QString::number(volume));
}
