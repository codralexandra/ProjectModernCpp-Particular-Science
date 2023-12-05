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
void RegisterWindow::onRegisterButtonClicked()
{
	QString email = ui.emailInput->text();
	QString username = ui.usernameInput->text();
	QString password = ui.passwordInput->text();
	if (validateUserPassword(password))
	{
		HashMethod pass;
		pass.Set(password.toStdString().c_str());
	}
	else
	{
		//add error
	}

}