#include "mainwindow.h"
#include "joingame.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.createGameButton, &QPushButton::clicked, this, &MainWindow::on_createButton_clicked);
	connect(ui.profileButton, &QPushButton::clicked, this, &MainWindow::on_profileButton_clicked);
	themeManager = &ThemeManager::instance();
	connect(themeManager, &ThemeManager::themeChanged, this, &MainWindow::handleThemeChanged);
	//this->setStyleSheet(themeManager->getCurrentStyleSheet());
}

MainWindow::~MainWindow()
{}

void MainWindow::SetUsername(const std::string& username)
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
	createGameWindow->setStyleSheet(themeManager->getCurrentStyleSheet());
	//this->hide();
}

void MainWindow::on_joinButton_clicked()
{
	JoinGame* joinWindow = new JoinGame;
	joinWindow->SetUsername(m_username);
	//this->close();
	joinWindow->show();
	joinWindow->setStyleSheet(themeManager->getCurrentStyleSheet());
}

void MainWindow::on_profileButton_clicked()
{
	profileWindow.setUsername(m_username);
	profileWindow.show();
	profileWindow.setStyleSheet(themeManager->getCurrentStyleSheet());
}

void MainWindow::handleThemeChanged(const QString& styleSheet)
{
	this->setStyleSheet(styleSheet);
}