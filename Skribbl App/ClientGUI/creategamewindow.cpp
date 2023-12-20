#include "creategamewindow.h"
#include <random>
#include <ctime>

CreateGameWindow::CreateGameWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CreateGameWindow::~CreateGameWindow()
{}


void CreateGameWindow::on_createLobbyButton_clicked()
{
	lobby = new Lobby;
	std::string string{ ui.difficultyBox[ui.difficultyBox->currentIndex()].itemData(ui.difficultyBox->currentIndex()).toString().toUtf8() };
	lobby->SetDifficulty(string);
	
	this->close();
	lobby->show();
}