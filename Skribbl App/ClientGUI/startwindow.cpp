#include "startwindow.h"

StartWindow::StartWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

StartWindow::~StartWindow()
{}

void StartWindow::recievePixelFromServer()
{

}

void StartWindow::WordToBeGuessed()
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:18080/game/word" });
	if (response.status_code == 200)
	{
		// If the request was successful (status code 200)
		// Parse the JSON response
		crow::json::rvalue jsonResponse = crow::json::load(response.text);
		ui.wordLabel->setText(QString::fromStdString(jsonResponse.s()));
	}
}

void StartWindow::updatePlayerRole(bool role)
{
	//get the role status from server here
	//false -> guessing, true -> drawing
	isDrawing = role;
	ui.notDrawingWidget->setVisible(!role);
	update();
}
