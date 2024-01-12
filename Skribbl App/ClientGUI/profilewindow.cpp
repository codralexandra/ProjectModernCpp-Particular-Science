#include "profilewindow.h"

profileWindow::profileWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(ui.historyList);
	themeManager = &ThemeManager::instance();
	connect(themeManager, &ThemeManager::themeChanged, this, &profileWindow::handleThemeChanged);
}

profileWindow::~profileWindow()
{}

void profileWindow::setUsername(std::string username)
{
	m_username = username;
}

void profileWindow::on_refreshHistoryButton_clicked()
{
	//delete previous history
	ui.historyList->clear();

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
			std::vector<int>{ jsonResponse["history"].begin(),jsonResponse["history"].end() };
		for (const auto& pair : history) {
			QString itemText = QString("Score: %1").arg(pair);
			ui.historyList->addItem(itemText);
		}

		m_averageScore = std::accumulate(history.begin(), history.end(), 0.0) / history.size();

		QString labelValue = QString::number(m_averageScore, 'f', 2); 
		ui.averageScore->setText(labelValue);

	}

	update();
}

void profileWindow::handleThemeChanged(const QString& styleSheet)
{
	this->setStyleSheet(styleSheet);
}