#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_joinButton_clicked();
	void on_createButton_clicked();

private:
	Ui::MainWindowClass ui;
};
