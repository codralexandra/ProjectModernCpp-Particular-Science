#include "creategamewindow.h"
#include <random>
#include <ctime>
#include <crow.h>
#include <cpr/cpr.h>

CreateGameWindow::CreateGameWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	themeManager = &ThemeManager::instance();
	connect(themeManager, &ThemeManager::themeChanged, this, &CreateGameWindow::handleThemeChanged);
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
	QString text(ui.difficultyBox->currentText());
	std::string string{ text.toUtf8() };;
	crow::json::wvalue jsonPayload;

	jsonPayload["Difficulty"] = string;
	jsonPayload["Username"] = m_username;
	std::string jsonString = jsonPayload.dump();
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/lobby" },
		cpr::Body{ jsonString },
		cpr::Header{ { "Content-Type", "application/json" } } // Specify JSON content type
	);
	
	if (response.status_code == 200)
	{
		auto responseBody = crow::json::load(response.text);
		if (!responseBody)
		{
			ui.errorLabel->setText("Invalid JSON format");
		}
		else
		{
			uint16_t id = responseBody["gameId"].i();
			lobby = new Lobby;
			lobby->SetGameID(id);
			lobby->SetDifficulty(string);
			this->close();
			lobby->SetUsername(m_username);
			lobby->SetGameMaster(true);
			lobby->show();
		}
	}
	else
	{
		if (!response.text.empty())
		{
			QString errorMessage = QString::fromUtf8(response.text);
			ui.errorLabel->setText(errorMessage);
		}
		else
		{
			ui.errorLabel->setText("Game creation failed: Server is closed!");
		}
	}
		
}

void CreateGameWindow::handleThemeChanged(const QString& styleSheet) {
	this->setStyleSheet(styleSheet);
}