#pragma once

#include <QMainWindow>
#include "ui_startwindow.h"
#include <cpr/cpr.h>
#include <crow.h>
#include"drawingwidget.h"
#include "thememanager.h"

class StartWindow : public QMainWindow
{
	Q_OBJECT

public:
	StartWindow(QWidget* parent = nullptr);
	~StartWindow();
	void SetUsername(const std::string& name);
	std::string GetUsername() const;
	void connectionToRoute();
	void WordToBeGuessed();
	void recievePixelFromServer();
	//void updatePlayerRole();
	void on_guessButton_clicked();
	void waitInLobby();
	void updateStartWindow();
	void onUpdateTextEdit(const QString& text);
	void onUpdateRole(bool isDrawing);
	void onUpdateGuess();
	void onUpdateDrawing(double x, double y, const QString& penColor, uint32_t penWidth);

signals:
	void updateTextEdit(const QString& text);
	void updateRole(bool isDrawing);
	void updateGuess();
	void updateDrawing(double x, double y, const QString& penColor, uint32_t penWidth);

private slots:
	void handleThemeChanged(const QString& styleSheet);
	void on_blackButton_clicked();
	void on_redButton_clicked();
	void on_blueButton_clicked();
	void on_greenButton_clicked();
	void on_yellowButton_clicked();
	void on_pinkButton_clicked();
	void on_purpleButton_clicked();
	void on_brownButton_clicked();

private:
	Ui::StartWindowClass ui;
	bool isDrawing;
	std::string m_username;
	drawingWidget* enableDrawing;
	ThemeManager* themeManager;
};
