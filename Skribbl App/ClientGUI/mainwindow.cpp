#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.createGameButton, &QPushButton::clicked, this, &MainWindow::on_createButton_clicked);
}

MainWindow::~MainWindow()
{}

void MainWindow::SetUsername(const std::string & username)
{
	m_username = username;
}

std::string MainWindow::GetUsername() const
{
	return m_username;
}

void MainWindow::on_createButton_clicked()
{
	createGameWindow = new CreateGameWindow;
	createGameWindow->SetUsername(m_username);
	createGameWindow->show();
}

void MainWindow::on_joinButton_clicked()
{

}