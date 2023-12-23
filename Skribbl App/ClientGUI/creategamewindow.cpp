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
	QString text(ui.difficultyBox->currentText());
	std::string string{ text.toUtf8() };
	lobby->SetDifficulty(string);
	uint16_t id;
	std::random_device RD; // random device to generate a seed for the random number engine
	std::mt19937 engine(RD()); // Mersenne Twister pseudo-random number engine, seeded with the random device
	std::uniform_int_distribution<> distr(0, 10); // uniform distribution for integers within [0, productions.size() - 1]

	id = distr(engine);
	this->close();
	lobby->show();
	lobby->SetGameID(id);
}