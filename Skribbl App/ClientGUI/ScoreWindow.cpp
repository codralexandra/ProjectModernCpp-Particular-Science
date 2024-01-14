#include "ScoreWindow.h"

ScoreWindow::ScoreWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->setStyleSheet(themeManager->getCurrentStyleSheet());
}

ScoreWindow::~ScoreWindow()
{}

void ScoreWindow::getPlayerScores(crow::json::rvalue jsonPackage)
{
	std::vector<std::string>playerUsernames{ jsonPackage["playersUsernames"].begin(),jsonPackage["playersUsernames"].end() };
	std::vector<int>playerScores{ jsonPackage["playerScores"].begin(),jsonPackage["playerScores"].end() };
	QString itemText;
	for (int i = 0 ;i < playerScores.size();i++)
	{
		itemText += QString("Username: ");
		itemText += QString::fromUtf8(playerUsernames[i]);
		itemText += QString(" - ");
		itemText += QString::number(playerScores[i]);
		itemText += '\n';

	}

	ui.scoreList->setText(itemText);

	std::string winner = playerUsernames[0];

	QString winnerLabel = QString("Congratulations!") + QString::fromUtf8(winner) + QString("has won!");

	ui.winnerLabel->setText(winnerLabel);
	update();
}

void ScoreWindow::SetScoreListText(const QString& str)
{
	ui.scoreList->setText(str);
}

void ScoreWindow::SetWinnerLabelText(const QString& str)
{
	ui.winnerLabel->setText(str);
}

void ScoreWindow::handleThemeChange(const QString& styleSheet)
{
	this->setStyleSheet(styleSheet);
}

void ScoreWindow::on_closeButton_clicked()
{
	this->close();
}

