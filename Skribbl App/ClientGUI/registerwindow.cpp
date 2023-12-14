#include "registerwindow.h"
#include<iostream>
#include <qchar.h>
#include "HashingDLL/hash.h"

RegisterWindow::RegisterWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.registerButton, &QPushButton::clicked, this, &RegisterWindow::onRegisterButtonClicked);
	connect(ui.backButton, &QPushButton::clicked, this, &RegisterWindow::on_backButton_clicked);
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

	if (!validateUsername(username)  || !validateUserEmail(email) || !validateUserPassword(password))
	{
		//add error message like "Please ensure all fields are filled in before proceeding"
	}
	else
	{
		//pass.HashMethod::Set(password); probleme la hash
		crow::json::wvalue jsonPayload;
		jsonPayload["email"] = email;
		jsonPayload["username"] = username;
		jsonPayload["password"] = password;
		std::string jsonString = jsonPayload.dump();

		auto response = cpr::Put(
			cpr::Url{ "http://localhost:18080/register" },
			cpr::Body{ jsonString },
			cpr::Header{ { "Content-Type", "application/json" } } // Specify JSON content type
		);
	}


	//std::stringstream urlBuilder;
	//urlBuilder << "http://localhost:18080/register";
	//		   auto response = cpr::Get(cpr::Url{urlBuilder.str()},
	//									cpr::Parameters{{ "email", email.toStdString().c_str() },
	//			   { "username", username.toStdString().c_str() },
	//			   { "password", pass.Get() }});


}