#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.registerButton, &QPushButton::clicked, this, &LoginWindow::on_registerButton_clicked);
}

LoginWindow::~LoginWindow()
{}

void LoginWindow::on_registerButton_clicked()
{
	this->hide();
	m_registerWindow.show();
}
