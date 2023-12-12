#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.backButton, &QPushButton::clicked, this, &LoginWindow::on_backButton_clicked);
	connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);
}

LoginWindow::~LoginWindow()
{}

void LoginWindow::on_loginButton_clicked()
{
	//pack user inputs
	std::string email = "";
	std::string username{ ui.usernameInput->text().toUtf8() };
	std::string password{ ui.passwordInput->text().toUtf8() };

	crow::json::wvalue jsonPayload;
	jsonPayload["email"] = email;			//log in with username, email is not important
	jsonPayload["username"] = username;
	jsonPayload["password"] = password;
	std::string jsonString = jsonPayload.dump();
	//send to server to interogate user db
	//if server response is ok, open main window
	//else set qLabel to wrong username/password 
	ui.loginStateLabel->setText("Username/ Password combination is wrong.");
}

void LoginWindow::on_backButton_clicked()
{
	this->close();
}
