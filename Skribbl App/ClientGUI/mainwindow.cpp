#include "mainwindow.h"
#include "joingame.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_gameMaster = false;
	connect(ui.createGameButton, &QPushButton::clicked, this, &MainWindow::on_createButton_clicked);
	connect(ui.profileButton, &QPushButton::clicked, this, &MainWindow::on_profileButton_clicked);
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
	m_gameMaster = true;
	this->hide();
}

void MainWindow::on_joinButton_clicked()
{
	JoinGame* joinWindow = new JoinGame;
	joinWindow->SetUsername(m_username);
	this->close();
	m_gameMaster = false;
	joinWindow->show();
	
}

void MainWindow::on_profileButton_clicked()
{
	profileWindow.show();
}