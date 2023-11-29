#include "clientgui.h"

ClientGUI::ClientGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.startRegisterButton, &QPushButton::clicked, this, &ClientGUI::on_startRegisterButton_clicked);
}

ClientGUI::~ClientGUI()
{}

void ClientGUI::on_startRegisterButton_clicked()
{
    this->hide();
    m_registerWindow.show();
}