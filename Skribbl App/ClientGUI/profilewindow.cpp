#include "profilewindow.h"

profileWindow::profileWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	themeManager = &ThemeManager::instance();
	connect(themeManager, &ThemeManager::themeChanged, this, &profileWindow::handleThemeChanged);
}

profileWindow::~profileWindow()
{}

void profileWindow::setUsername(std::string username)
{
	m_username = username;
}

void profileWindow::on_refreshHistoryButton_clicked()//remake for new widgets
{
	//delete previous history
	//ui.historyList->clear();

	//send username to server
	crow::json::wvalue jsonPayload;
	jsonPayload["username"] = m_username;
	std::string jsonString = jsonPayload.dump();

	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/profile" },
		cpr::Body{ jsonString },
		cpr::Header{ { "Content-Type", "application/json" } }
	);

	//req from server & get json
	if (response.status_code == 200)
	{
		crow::json::rvalue jsonResponse = crow::json::load(response.text);
		std::vector<int> history =
			std::vector<int>{ jsonResponse["gameHistory"].begin(),jsonResponse["gameHistory"].end() };
		
		QString itemText;
		for (const auto& pair : history)
		{
			itemText += QString("Score: ");
			itemText += QString::number(pair);
			itemText += '\n';
			
		}


		ui.history->setText(itemText);

		m_averageScore = std::accumulate(history.begin(), history.end(), 0.0) / history.size();

		QString labelValue = QString::number(m_averageScore, 'f', 2); 
		
		ui.average->setText(labelValue);

	}

	update();
}

void profileWindow::handleThemeChanged(const QString& styleSheet)
{
	this->setStyleSheet(styleSheet);
}