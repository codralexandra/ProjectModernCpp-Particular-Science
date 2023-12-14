#include "loginwindow.h"
#include<iostream>
#include <qchar.h>
#include "HashingDLL/hash.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.backButton, &QPushButton::clicked, this, &LoginWindow::on_backButton_clicked);
	connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);
}

LoginWindow::~LoginWindow()
{}

bool LoginWindow::validateUserPassword(const std::string& m_password)
{

	bool allValid = std::regex_match(m_password, std::regex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{8,}$)"));

	return allValid;
}

bool LoginWindow::validateUsername(const std::string& m_username) {

	bool isValid = std::regex_match(m_username, std::regex(R"(^(?=.*[A-Za-z]{3,})[A-Za-z\d]+$)"));

	return isValid;
}

void LoginWindow::on_loginButton_clicked()
{
	std::string username{ ui.usernameInput->text().toUtf8() };
	std::string password{ ui.passwordInput->text().toUtf8() };
	HashMethod pass;
	if (!validateUsername(username))
	{
		ui.loginStateLabel->setText("Login failed: Invalid username. Username must contain at least 3 letters and can only include letters and numbers.");
	}
	else if (!validateUserPassword(password))
	{
		ui.loginStateLabel->setText("Login failed: Invalid password. Password must be at least 8 characters long and include at least one uppercase letter, one lowercase letter, and one digit.");
	}
	else
	{
		//pass.HashMethod::Set(password); probleme la hash
		crow::json::wvalue jsonPayload;
		jsonPayload["username"] = username;
		jsonPayload["password"] = password;
		std::string jsonString = jsonPayload.dump();

		auto response = cpr::Put(
			cpr::Url{ "http://localhost:18080/login" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } }
		);

		if (response.status_code != 200)
		{
			if (response.status_code >= 400 && response.status_code < 500)
			{
				ui.loginStateLabel->setText("Login failed: Incorrect username or password.");
			}
			else if (response.status_code >= 500 && response.status_code < 600)
			{
				ui.loginStateLabel->setText("Login failed: Network or server error. Please try again later.");
			}
			else
			{
				ui.loginStateLabel->setText("Login failed: Unexpected error. Please try again later.");
			}
		}
		else
		{
			//open the main window
		}
		
	}
}

void LoginWindow::on_backButton_clicked()
{
	this->close();
}
