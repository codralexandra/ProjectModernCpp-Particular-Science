#include "thememanager.h"

QString ThemeManager::getCurrentStyleSheet() const
{
	return currentStyleSheet;
}

ThemeManager& ThemeManager::instance()
{
	static ThemeManager instance;
	return instance;
}

void ThemeManager::setLightTheme()
{
	currentStyleSheet = "";
	currentStyleSheet =
		"QLabel#gameTitle{color: black;}"
		"QMainWindow { background: white; }"
		"QWidget#SettingsWindowClass { background: white; }"
		"QLabel { color: black; }"
		"QWidget#LoginWindowClass { background: white; }"
		"QWidget#RegisterWindowClass { background: white; }"
		"QWidget#JoinGameClass { background: white; }"
		"QWidget#CreateGameWindowClass { background: white; }"
		"QWidget#profileWindowClass { background: white; }";

	emit themeChanged(currentStyleSheet);
}

void ThemeManager::setBaseTheme()
{
	currentStyleSheet = "";
	currentStyleSheet =
		"QLabel#gameTitle { color: black; }"
		"QMainWindow { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }"
		"QWidget#SettingsWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }"
		"QLabel { color: black; }"
		"QWidget#LoginWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }"
		"QWidget#RegisterWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }"
		"QWidget#JoinGameClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }"
		"QWidget#CreateGameWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }"
		"QWidget#profileWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }";

	emit themeChanged(currentStyleSheet);
}

void ThemeManager::setDarkTheme()
{
	currentStyleSheet = "";
	currentStyleSheet =
		"QLabel#gameTitle { color: white; }"
		"QMainWindow { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255)); }"
		"QWidget#SettingsWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255)); }"
		"QLabel { color: white; }"
		"QWidget#LoginWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255)); }"
		"QWidget#RegisterWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255)); }"
		"QWidget#JoinGameClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255)); }"
		"QWidget#CreateGameWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255)); }"
		"QWidget#profileWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255)); }";

	emit themeChanged(currentStyleSheet);
}
