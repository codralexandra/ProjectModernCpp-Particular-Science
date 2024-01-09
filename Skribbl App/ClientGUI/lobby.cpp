#include "lobby.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <qstringlist.h>
#include<thread>
#include <functional>

Lobby::Lobby(QWidget* parent)
	: QWidget(parent)
{
	m_state = LobbyState::Waiting;
	ui.setupUi(this);
	connect(ui.startGameButton, &QPushButton::clicked, this, &Lobby::on_startGameButton_clicked);
}

Lobby::~Lobby()
{}



//Will be needed
//void Lobby::on_RefreshButton_clicked()
//{
//    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/playerjoined" });
//    if (response.status_code == 200) {
//        // If the request was successful (status code 200)
//        // Parse the JSON response
//        crow::json::rvalue jsonResponse = crow::json::load(response.text);
//
//        // Access the "players" array in the JSON response
//        const crow::json::rvalue& playersArray = jsonResponse["players"];
//
//        // Iterate through the player names and do something with them
//        for (const auto& playerName : playersArray) {
//            ui.PlayerListBox->addItem(QString::fromStdString(playerName.s())); // Assuming playerName is a string
//            // Do whatever you need with each player name
//        }
//    }
//    else {
//        // Handle error cases or non-200 status codes
//        std::cout << "Request failed: " << response.status_code << std::endl;
//    }
//    update();
//}


void Lobby::SetGameID(const uint16_t& id)
{
	m_gameID = id;
	ui.roomCode->setText(QString::number(id));
	update();
}

void Lobby::SetDifficulty(const std::string& diff)
{
	m_difficulty = diff;
}

void Lobby::SetGameMaster(const bool& gameMaster)
{
	m_gameMaster = gameMaster;
	ui.startGameButton->setVisible(m_gameMaster);
}



uint16_t Lobby::GetGameID() const
{
	return m_gameID;
}


std::string Lobby::GetDifficulty() const
{
	return m_difficulty;
}

bool Lobby::GetGameMaster() const
{
	return m_gameMaster;
}
//void Lobby::threadFuntion() {
//	Lobby lobbyInstance; // Declaration and initialization
//	lobbyInstance.setUIUpdateFunction(std::bind(&Lobby::updateGameWindow, &lobbyInstance));
//	lobbyInstance.PutOnWaiting();
//}
//void Lobby::updateGameWindow() {
//	// Code to update the UI, like showing the game window
//	gameWindow.show();
//}

//void Lobby::waitInLobby() {
//	cpr::Response response;
//	do {
//		response = cpr::Get(cpr::Url{"http://localhost:18080/lobby/waiting"});
//	} while (response.status_code == 201);
//
//	if (response.status_code == 200) {
//		if (uiUpdateFunction) {
//			uiUpdateFunction();
//		}
//	}
//}
void Lobby::waitInLobby() {
	cpr::Response response;
	do {
		response = cpr::Get(cpr::Url{"http://localhost:18080/lobby/waiting"});
	} while (response.status_code == 201);

	if (response.status_code == 200) {
		// Schedule updateGameWindow to be called in the main thread
		QMetaObject::invokeMethod(this, "updateGameWindow", Qt::QueuedConnection);
	}
}

void Lobby::updateGameWindow() {
	// This method is now safely executed in the main thread
	this->close();
	gameWindow.show();
}

//void Lobby::setUIUpdateFunction(const std::function<void()>& func) {
//	uiUpdateFunction = func;
//}
void Lobby::PutOnWaiting() {
	std::thread waitingThread(&Lobby::waitInLobby, this);
	waitingThread.detach();
}
void sendRequest() {
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/game" }
	);
}
void Lobby::on_startGameButton_clicked()
{
	this->close();
	gameWindow.show();
	std::thread requestThread(sendRequest);
	requestThread.detach();


}