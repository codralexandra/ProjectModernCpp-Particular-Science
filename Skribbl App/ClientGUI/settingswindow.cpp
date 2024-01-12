#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
	: QWidget(parent), soundManager(new SoundManager(this))
{
	ui.setupUi(this);
	connect(ui.songVolume, &QSlider::valueChanged, this, &SettingsWindow::setSoundVolume);
	ui.volumeValue->setText("Volume: " + QString::number(ui.songVolume->value()));
	themeManager = &ThemeManager::instance();
	connect(themeManager, &ThemeManager::themeChanged, this, &SettingsWindow::handleThemeChanged);
}

SettingsWindow::~SettingsWindow()
{}

void SettingsWindow::setSoundVolume(uint32_t volume)
{
	soundManager->setVolume(volume);
	ui.volumeValue->setText("Volume: " + QString::number(volume));
}

void SettingsWindow::on_darkThemeButton_clicked()
{
	ThemeManager::instance().setDarkTheme();
}

void SettingsWindow::on_lightThemeButton_clicked()
{
	ThemeManager::instance().setLightTheme();
}

void SettingsWindow::on_colorThemeButton_clicked()
{
	ThemeManager::instance().setBaseTheme();
}

void SettingsWindow::handleThemeChanged(const QString& styleSheet) {
	this->setStyleSheet(styleSheet);
}
