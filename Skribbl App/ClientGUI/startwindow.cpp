#include "startwindow.h"

StartWindow::StartWindow(QWidget* parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
	enableDrawing = ui.drawingView;
	connect(ui.guessButton, &QPushButton::clicked, this, &StartWindow::on_guessButton_clicked);
}

StartWindow::~StartWindow()
{}

void StartWindow::on_guessButton_clicked()
{
	crow::json::wvalue jsonPayload;
	jsonPayload["username"] = m_username;
	std::string word { ui.wordInput->text().toUtf8() };
	for (char& c : word) {
		c = std::tolower(c);
	}
	if (!word.empty()) {
		word[0] = std::toupper(word[0]);
	}
	jsonPayload["Guess"] = word;
	std::string jsonString = jsonPayload.dump();
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/game/tryguess" },
		cpr::Body{ jsonString },
		cpr::Header{ { "Content-Type", "application/json" } }
	);
	if (response.status_code == 200)
	{
		ui.rightResponseLabel->setText("You guessed the word!");
		ui.notDrawingWidget->setEnabled(false);
		ui.notDrawingWidget->setVisible(false);
		ui.centralWidget->setEnabled(true);
	}
	else if (response.status_code == 201)
	{
		ui.wrongResponseLabel->setText("The word is wrong!");
	}
	else
	{
		//error
	}
}
void StartWindow::recievePixelFromServer()
{

}

void StartWindow::SetUsername(const std::string& name)
{
	m_username = name;
}

std::string StartWindow::GetUsername() const
{
	return m_username;
}

void StartWindow::connectionToRoute()
{
	crow::json::wvalue jsonPayload;
	jsonPayload["username"] = m_username;
	std::string jsonString = jsonPayload.dump();
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/game/startround" },
		cpr::Body{ jsonString },
		cpr::Header{ { "Content-Type", "application/json" } }
	);
	if (response.status_code == 200)
	{
		auto responseBody = crow::json::load(response.text);
		if (!responseBody)
		{
			//error
		}
		else
		{
			updatePlayerRole(responseBody);
			//update();
		}
	}
	else
	{
		if (!response.text.empty())
		{
			//error
		}
		else
		{
			//error
		}
	}
}

void StartWindow::WordToBeGuessed()
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:18080/game/word" });
	if (response.status_code == 200)
	{
		// If the request was successful (status code 200)
		// Parse the JSON response
		crow::json::rvalue jsonResponse = crow::json::load(response.text);
		//ui.wordLabel->setText(QString::fromStdString(jsonResponse.s()));
	}
}


void StartWindow::updatePlayerRole(crow::json::rvalue jsonBody)
{
	//get the role status from server here
	//false -> guessing, true -> drawing
	isDrawing = jsonBody["isDrawing"].b();
	if (!isDrawing)
	{

		ui.notDrawingWidget->setEnabled(true);
		ui.drawingView->setEnabled(false);
		enableDrawing->setEnable(false);
	}
	else
	{
		ui.notDrawingWidget->setEnabled(false);
		ui.notDrawingWidget->setVisible(false);
		ui.centralWidget->setEnabled(true);
		enableDrawing->setEnable(true);
	}
	std::string word = jsonBody["word"].s();
	QString qword = QString::fromUtf8(word.c_str());
	ui.textEdit->setText(qword);
	//ui.wordLabel->setVisible(true);
	//ui.wordLabel->setEnabled(true);
	//update();
	//this->repaint();
	update();
}
