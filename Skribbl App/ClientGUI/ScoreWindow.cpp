#include "ScoreWindow.h"

ScoreWindow::ScoreWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setStyleSheet(themeManager->getCurrentStyleSheet());
}

ScoreWindow::~ScoreWindow()
{}

//void ScoreWindow::getPlayerScores(crow::json::wvalue jsonPackage)
//{
//	auto response = cpr::Put(
//		cpr::Url{ "http://localhost:18080/profile" },
//		cpr::Body{  },
//		cpr::Header{ { "Content-Type", "application/json" } }
//	);
//
//	if (response.status_code == 200)
//	{
//		crow::json::rvalue jsonResponse = crow::json::load(response.text);
//		std::vector<std::pair<std::string,int>> scoreList =
//			std::vector<std::pair<std::string, int>>{ jsonResponse["finalScore"].begin(),jsonResponse["finalScore"].end() };
//
//		QString itemText;
//		for (const auto& pair : scoreList)
//		{
//			itemText += QString("Username: ");
//			itemText += QString::fromUtf8(pair.first);
//			itemText += QString(" - ");
//			itemText += QString::number(pair.second);
//			itemText += '\n';
//
//		}
//
//		ui.scoreList->setText(itemText);
//
//		std::string winner = scoreList[0].first;
//
//		QString winnerLabel = QString("Congratulations!") + QString::fromUtf8(winner) + QString("has won!");
//
//		ui.winnerLabel->setText(winnerLabel);
//	}
//
//	update();
//}

void ScoreWindow::handleThemeChange(const QString & styleSheet)
{
	this->setStyleSheet(styleSheet);
}

void ScoreWindow::on_closeButton_clicked()
{
	this->close();
}

