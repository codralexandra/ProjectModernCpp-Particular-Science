#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.backButton, &QPushButton::clicked, this, &LoginWindow::on_backButton_clicked);
}

LoginWindow::~LoginWindow()
{}

void LoginWindow::on_backButton_clicked()
{
	this->close();
}
