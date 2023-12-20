#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.createGameButton, &QPushButton::clicked, this, &MainWindow::on_createButton_clicked);
}

MainWindow::~MainWindow()
{}

void MainWindow::on_createButton_clicked()
{
	createGameWindow = new CreateGameWindow;
	createGameWindow->show();
}

void MainWindow::on_joinButton_clicked()
{

}