#include "clientgui.h"

ClientGUI::ClientGUI(QWidget *parent)
    : QMainWindow(parent)
{
    soundManager = &SoundManager::GetInstance();
    ui.setupUi(this);
    connect(ui.startRegisterButton, &QPushButton::clicked, this, &ClientGUI::on_startRegisterButton_clicked);
    connect(ui.startLoginButton, &QPushButton::clicked, this, &ClientGUI::on_startLoginButton_clicked);
    connect(ui.exitButton, &QPushButton::clicked, this, &ClientGUI::on_exitButton_clicked);
    connect(ui.soundMuteCheck, &QRadioButton::toggled, this,&ClientGUI::on_soundMuteCheck_toggled);
}

ClientGUI::~ClientGUI()
{}

void ClientGUI::on_startRegisterButton_clicked()
{
    //this->hide();
    m_registerWindow.show();
}

void ClientGUI::on_startLoginButton_clicked()
{
    //this->hide();
    m_loginWindow.show();
}

void ClientGUI::on_exitButton_clicked()
{
    this->close();
}

void ClientGUI::on_soundMuteCheck_toggled(bool checked)
{
    soundManager->setMuted(checked);
}

void ClientGUI::on_settingsButton_clicked()
{
    m_settingsWindow.show();
}
