#include "creategamewindow.h"
#include <random>
#include <ctime>
#include <crow.h>
#include <cpr/cpr.h>

CreateGameWindow::CreateGameWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CreateGameWindow::~CreateGameWindow()
{}

void CreateGameWindow::SetUsername(const std::string & username)
{
	m_username = username;
}

std::string CreateGameWindow::GetUsername() const
{
	return m_username;
}


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
	crow::json::wvalue jsonPayload;
	jsonPayload["RoomCode"] = lobby->GetGameID();
	jsonPayload["Difficulty"] = lobby->GetDifficulty();
	jsonPayload["Username"] = m_username;
	std::string jsonString = jsonPayload.dump();
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/lobby" },
		cpr::Body{ jsonString },
		cpr::Header{ { "Content-Type", "application/json" } } // Specify JSON content type
	);

}