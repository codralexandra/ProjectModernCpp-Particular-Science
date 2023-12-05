#include "registerwindow.h"
import hash;
RegisterWindow::RegisterWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.registerButton, &QPushButton::clicked, this, &RegisterWindow::onRegisterButtonClicked);
}

RegisterWindow::~RegisterWindow()
{}
bool RegisterWindow::validateUserPassword(QString m_password)
{

	bool allValid = std::regex_match(m_password.toStdString().c_str(), std::regex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{8,}$)"));
	if (!allValid) {
		return false;
	}
	return true;
}
bool RegisterWindow::validateUserEmail(QString m_email)
{
	bool emailValid;
	emailValid = std::regex_match(m_email.toStdString().c_str(), std::regex(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))"));
	if (!emailValid) {
		return false;
	}
	return true;
}
void RegisterWindow::onRegisterButtonClicked()
{
	QString email = ui.emailInput->text();
	QString username = ui.usernameInput->text();
	QString password = ui.passwordInput->text();
	HashMethod pass;
	if (validateUserPassword(password))
	{
		pass.Set(password.toStdString().c_str());
	}
	else
	{
		//add error -> with exit function
	}
	if (!validateUserEmail(email))
	{
		//add error ->exit function
	}
	//add function verify username with database
	/*auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/register" },
		cpr::Payload{
			{ "email", email.toStdString().c_str() },
			{ "username", username.toStdString().c_str() },
			{ "password", pass.Get()}
	}
	);*/
	/*std::stringstream urlBuilder;
	urlBuilder << "http://localhost:18080/register";
			   auto response = cpr::Get(cpr::Url{urlBuilder.str()},
										cpr::Parameters{{ "email", email.toStdString().c_str() },
				   { "username", username.toStdString().c_str() },
				   { "password", pass.Get() }});*/


}