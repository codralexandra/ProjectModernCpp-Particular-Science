#include "clientgui.h"

ClientGUI::ClientGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.startRegisterButton, &QPushButton::clicked, this, &ClientGUI::on_startRegisterButton_clicked);
    connect(ui.startLoginButton, &QPushButton::clicked, this, &ClientGUI::on_startLoginButton_clicked);
    sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile("./Sounds/MainMenu.wav"));
    sound->setVolume(10.0);
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->play();
    connect(ui.songVolume, &QSlider::valueChanged, this, [this](int value) {
        qreal volume = qreal(value) / 100.0;
        sound->setVolume(volume);
        });
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