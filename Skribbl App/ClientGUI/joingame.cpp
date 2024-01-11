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
	if (response.status_code == 200)
	{
		Lobby* lobby = new Lobby;
		auto response2 = cpr::Get(
			cpr::Url{ "http://localhost:18080/game/difficulty" }
		);
		if (response2.status_code == 200)
		{
			crow::json::rvalue jsonResponse = crow::json::load(response2.text);
			lobby->SetDifficulty(jsonResponse["Difficulty"].s());
			lobby->SetGameID(ui.insertRoomCode->text().toInt());
			this->close();
			lobby->SetGameMaster(false);
			lobby->SetUsername(m_username);
			lobby->show();
			lobby->PutOnWaiting();
		}

		/*ui.errorMsg->clear();
		ui.errorMsg->setText(QString::fromStdString(response.status_line));*/
	}
}

