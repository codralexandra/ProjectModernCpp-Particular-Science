#include "joingame.h"
#include <cpr/cpr.h>
#include <crow.h>

JoinGame::JoinGame(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//connect(ui.joinGameButton,)
}

JoinGame::~JoinGame()
{}

void JoinGame::SetUsername(const std::string& name)
{
	m_username = name;
}

std::string JoinGame::GetUsername() const
{
	return m_username;
}

void JoinGame::on_joinGameButton_clicked()
{
	std::string roomCode{ ui.insertRoomCode->text().toUtf8() };
	crow::json::wvalue jsonPayload;
	jsonPayload["username"] = this->m_username;
	jsonPayload["RoomCode"] = roomCode;
	std::string jsonString = jsonPayload.dump();
	cpr::Response response;
	response = cpr::Put(
		cpr::Url{ "http://localhost:18080/playerjoined" },
		cpr::Body{ jsonString },
		cpr::Header{ { "Content-Type", "application/json" } }

	);
	ui.errorMsg->clear();
	ui.errorMsg->setText(QString::fromStdString(response.status_line));
}

