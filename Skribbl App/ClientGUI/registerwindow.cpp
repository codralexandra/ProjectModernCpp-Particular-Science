#include "registerwindow.h"
#include<iostream>
#include <qchar.h>
#include "HashingDLL/hash.h"

RegisterWindow::RegisterWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.passwordInput->setEchoMode(QLineEdit::Password);
	connect(ui.registerButton, &QPushButton::clicked, this, &RegisterWindow::onRegisterButtonClicked);
	connect(ui.backButton, &QPushButton::clicked, this, &RegisterWindow::on_backButton_clicked);
	themeManager = &ThemeManager::instance();
	connect(themeManager, &ThemeManager::themeChanged, this, &RegisterWindow::handleThemeChanged);
}

RegisterWindow::~RegisterWindow()
{}

void RegisterWindow::on_backButton_clicked()
{
	this->close();
}

bool RegisterWindow::validateUserPassword(const std::string& m_password)
{

	bool allValid = std::regex_match(m_password, std::regex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{8,}$)"));

	return allValid;
}

bool RegisterWindow::validateUserEmail(const std::string& m_email)
{
	bool emailValid = std::regex_match(m_email, std::regex(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))"));

	return emailValid;
}
bool RegisterWindow::validateUsername(const std::string& m_username) {

	bool isValid = std::regex_match(m_username, std::regex(R"(^(?=.*[A-Za-z]{3,})[A-Za-z\d]+$)"));

	return isValid;
}


void RegisterWindow::onRegisterButtonClicked()
{
	std::string email{ ui.emailInput->text().toUtf8() };
	std::string username{ ui.usernameInput->text().toUtf8() };
	std::string password{ ui.passwordInput->text().toUtf8() };
	HashMethod pass;

	if (!validateUserEmail(email))
	{
		//ui.registerStateLabel->setText("Registration failed: Invalid email format. Please enter a valid email address (e.g., user@example.com).");
	}
	else if (!validateUsername(username))
	{
		//ui.registerStateLabel->setText("Registration failed: Invalid username. Username must contain at least 3 letters and can only include letters and numbers.");
	}
	else if (!validateUserPassword(password))
	{
		//ui.registerStateLabel->setText("Registration failed: Invalid password. Password must be at least 8 characters long and include at least one uppercase letter, one lowercase letter, and one digit.");
	}
	else
	{
		//pass.HashMethod::Set(password); probleme la hash
		crow::json::wvalue jsonPayload;
		jsonPayload["email"] = email;
		jsonPayload["username"] = username;
		jsonPayload["password"] = password;
		std::string jsonString = jsonPayload.dump();

		auto response = cpr::Post(
			cpr::Url{ "http://localhost:18080/register" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } } // Specify JSON content type
		);

		if (response.status_code != 200)
		{
			if (response.status_code >= 400 && response.status_code < 500)
			{
				//ui.registerStateLabel->setText("Registration failed: The email or username is already in use. Please try a different one.");
			}
			else if (response.status_code >= 500 && response.status_code < 600)
			{
				//ui.registerStateLabel->setText("Registration failed: Network or server error. Please try again later.");
			}
			else
			{
				//ui.registerStateLabel->setText("Registration failed: Unexpected error. Please try again later.");
			}
		}
		else
		{
			//open the main window
		}
	}
}

void RegisterWindow::handleThemeChanged(const QString& styleSheet)
{
	this->setStyleSheet(styleSheet);
}