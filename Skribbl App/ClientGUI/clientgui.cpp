#include "clientgui.h"

ClientGUI::ClientGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.startRegisterButton, &QPushButton::clicked, this, &ClientGUI::on_startRegisterButton_clicked);
    connect(ui.startLoginButton, &QPushButton::clicked, this, &ClientGUI::on_startLoginButton_clicked);
}

ClientGUI::~ClientGUI()
{}

void ClientGUI::on_startRegisterButton_clicked()
{
    this->hide();
    m_registerWindow.show();
}

void ClientGUI::on_startLoginButton_clicked()
{
    this->hide();
    m_loginWindow.show();
}