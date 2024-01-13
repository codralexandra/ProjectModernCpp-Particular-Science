#include "startwindow.h"
#include<thread>;
#include <qcolor.h>
#include<chrono>

StartWindow::StartWindow(QWidget* parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
	enableDrawing = ui.drawingView;
	connect(ui.guessButton, &QPushButton::clicked, this, &StartWindow::on_guessButton_clicked);
	themeManager = &ThemeManager::instance();
	connect(themeManager, &ThemeManager::themeChanged, this, &StartWindow::handleThemeChanged);
	connect(this, &StartWindow::updateTextEdit, this, &StartWindow::onUpdateTextEdit);
	connect(this, &StartWindow::updateRole, this, &StartWindow::onUpdateRole);
	connect(this, &StartWindow::updateGuess, this, &StartWindow::onUpdateGuess);
	connect(this, &StartWindow::updateDrawing, this, &StartWindow::onUpdateDrawing);
	this->setStyleSheet(themeManager->getCurrentStyleSheet());
}

StartWindow::~StartWindow()
{}

void StartWindow::on_guessButton_clicked()
{
	crow::json::wvalue jsonPayload;
	jsonPayload["username"] = m_username;
	std::string word{ ui.wordInput->text().toUtf8() };
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
		emit updateGuess();
	}
	else if (response.status_code == 201)
	{
		ui.wrongResponseLabel->setText("The word is wrong!");
	}
	else if (response.status_code == 203)
	{
		ui.wrongResponseLabel->setText("The word is already guessed!");
	}
	else
	{
		//empty
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


//void StartWindow::updatePlayerRole()
//{
//	//get the role status from server here
//	//false -> guessing, true -> drawing
//	if (!isDrawing)
//	{
//		ui.notDrawingWidget->setEnabled(true);
//		ui.drawingView->setEnabled(false);
//		enableDrawing->setEnable(false);
//	}
//	else
//	{
//		ui.notDrawingWidget->setEnabled(false);
//		ui.notDrawingWidget->setVisible(false);
//		ui.centralWidget->setEnabled(true);
//		enableDrawing->setEnable(true);
//	}
//	/*std::string word = jsonBody["word"].s();
//	QString qword = QString::fromUtf8(word.c_str());
//	ui.textEdit->setText(qword);*/
//	update();
//}

void StartWindow::handleThemeChanged(const QString& styleSheet) {
	this->setStyleSheet(styleSheet);
}

void StartWindow::onUpdateTextEdit(const QString& text) {
	ui.textEdit->setText(text);
	//update();
}
void StartWindow::onUpdateDrawing(double x, double y, const QString& penColor, uint32_t penWidth, bool newLine) {
	enableDrawing->receivePixelFromServer(x,y,penColor, penWidth,newLine);
}

void StartWindow::onUpdateGuess() {
	ui.rightResponseLabel->setText("You guessed the word!");
	ui.notDrawingWidget->setEnabled(false);
	ui.notDrawingWidget->setVisible(false);
	update();
}

void StartWindow::on_blackButton_clicked()
{
	enableDrawing->setPenColor(QColor(0, 0, 0));
}

void StartWindow::on_redButton_clicked()
{
	enableDrawing->setPenColor(QColor(255, 0, 0));
}

void StartWindow::on_blueButton_clicked()
{
	enableDrawing->setPenColor(QColor(52, 152, 219));
}

void StartWindow::on_greenButton_clicked()
{
	enableDrawing->setPenColor(QColor(0, 128, 0));
}

void StartWindow::on_yellowButton_clicked()
{
	enableDrawing->setPenColor(QColor(255, 255, 0));
}

void StartWindow::on_pinkButton_clicked()
{
	enableDrawing->setPenColor(QColor(255, 192, 203));
}

void StartWindow::on_purpleButton_clicked()
{
	enableDrawing->setPenColor(QColor(128, 0, 128));
}

void StartWindow::on_brownButton_clicked()
{
	enableDrawing->setPenColor(QColor(150, 75, 0));
}

void StartWindow::onUpdateRole(bool isDrawing) {
	if (!isDrawing)
	{
		ui.notDrawingWidget->setEnabled(true);
		ui.drawingView->setEnabled(false);
		enableDrawing->setEnable(false);
		ui.notDrawingWidget->setVisible(true);
		ui.blackButton->setVisible(false);
		ui.redButton->setVisible(false);
		ui.blueButton->setVisible(false);
		ui.greenButton->setVisible(false);
		ui.yellowButton->setVisible(false);
		ui.pinkButton->setVisible(false);
		ui.purpleButton->setVisible(false);
		ui.brownButton->setVisible(false);
		ui.widthSlider->setVisible(false);
		//enableDrawing->clearWidget();
	}
	else
	{
		ui.drawingView->setEnabled(true);
		ui.notDrawingWidget->setEnabled(false);
		ui.notDrawingWidget->setVisible(false);
		enableDrawing->setEnable(true);
		ui.blackButton->setVisible(true);
		ui.redButton->setVisible(true);
		ui.blueButton->setVisible(true);
		ui.greenButton->setVisible(true);
		ui.yellowButton->setVisible(true);
		ui.pinkButton->setVisible(true);
		ui.purpleButton->setVisible(true);
		ui.brownButton->setVisible(true);
		ui.widthSlider->setVisible(true);
		//ui.drawingView->clearWidget();
	}

}



void StartWindow::waitInLobby() {
	cpr::Response response;
	do {
		crow::json::wvalue jsonPayload;
		jsonPayload["username"] = m_username;
		std::string jsonString = jsonPayload.dump();
		response = cpr::Get(cpr::Url{ "http://localhost:18080/game/package" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } } // Specify JSON content type
		);
		auto responseBody = crow::json::load(response.text);
		if (responseBody.has("isDrawing")) {
			isDrawing = responseBody["isDrawing"].b();
			emit updateRole(isDrawing);
		}
		if (responseBody.has("word")) {
			std::string word = responseBody["word"].s();
			QString qword = QString::fromUtf8(word.c_str());
			emit updateTextEdit(qword);
		}
		if (responseBody.has("x")) {
			const auto& xValues = responseBody["x"];
			const auto& yValues = responseBody["y"];
			const auto& widths = responseBody["penWidth"];
			const auto& colors = responseBody["color"];
			const auto& newLines = responseBody["newLine"];

			for (size_t i = 0; i < xValues.size(); ++i) {
				double x = xValues[i].d();
				double y = yValues[i].d();
				int width = widths[i].i();
				std::string color = colors[i].s();
				std::string newLineString = newLines[i].s();
				bool newLine = (newLineString[0] == '1');
				QString qColor = color.c_str();;
				// Emit signal for each drawing point
				emit updateDrawing(x, y, qColor, width, newLine);
			}
			
		}
		if (isDrawing == true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(63000));
			isDrawing = false;
			emit updateRole(isDrawing);
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		//add pixel
	} while (response.status_code == 200);

	if (response.status_code == 201) {
		// Schedule updateGameWindow to be called in the main thread
		//QMetaObject::invokeMethod(this, "updateGameWindow", Qt::QueuedConnection);
	}
}
//void StartWindow::fastRoute()
//{
//	std::thread waitingThread(&StartWindow::waitInLobby, this);
//	//std::thread waitingThread2(&StartWindow::waitInLobby, this);
//	//std::thread waitingThread3(&StartWindow::waitInLobby, this);
//	/*for (int i = 4; i >= 0; i++)
//	{
//		std::thread waitingThread(&StartWindow::waitInLobby, this);
//		waitingThread.detach();
//	}*/
//	waitingThread.detach();
//	//waitingThread2.detach();
//	//waitingThread3.detach();
//}
void StartWindow::connectionToRoute()
{
	std::thread waitingThread(&StartWindow::waitInLobby, this);
	waitingThread.detach();
}

