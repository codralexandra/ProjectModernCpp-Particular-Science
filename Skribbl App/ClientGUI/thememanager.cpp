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
	currentStyleSheet =
		"QMainWindow { background-color: white; }";
		"QWidget { background-color: rgba(255, 255, 255, 200); border - radius: 20px; }";
		"QWidet#SettingsWindowClass { background-color: white;}";

	emit themeChanged(currentStyleSheet);
}

void ThemeManager::setBaseTheme()
{
	currentStyleSheet =
		"QMainWindow { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }";
		"QWidget { background-color: rgba(255, 255, 255, 200); border - radius: 20px; }";
		"QWidget#SettingsWindowClass { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.75, y2:0.79, stop:0 rgba(255, 190, 230, 255), stop:1 rgba(220, 217, 255, 255), x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 231, 251, 255), stop:1 rgba(210, 230, 255, 255)); }";

	emit themeChanged(currentStyleSheet);
}

void ThemeManager::setDarkTheme()
{
	currentStyleSheet =
		"QLabel#gameTitle{color: white;}"
		"QMainWindow{ background :qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255));}"
		//"QWidget{background-color: darkGrey; border-radius: 20px;}" find a way to make this darker and not override main window
		"QWidget#SettingsWindowClass{ background :qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255));}"
		"QLabel{color: white;}"
		"QWidget#LoginWindowClass{ background:qlineargradient(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop : 0 rgba(0, 0, 0, 255), stop : 1 rgba(63, 63, 127, 255)); }"
		"QWidget#RegisterWindowClass{ background :qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(63, 63, 127, 255));}";		

	emit themeChanged(currentStyleSheet);
}
