#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_clientgui.h"
#include "registerwindow.h"
#include "loginwindow.h"
#include <qsoundeffect>

class ClientGUI : public QMainWindow
{
    Q_OBJECT

public:
    ClientGUI(QWidget *parent = nullptr);
    ~ClientGUI();

private slots:
    void on_startRegisterButton_clicked();
    void on_startLoginButton_clicked();
    void on_exitButton_clicked();
    //void on_settingsButton_clicked();

private:
    Ui::ClientGUIClass ui;
    RegisterWindow m_registerWindow;
    LoginWindow m_loginWindow;
    QSoundEffect* sound;
};
