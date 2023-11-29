#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_clientgui.h"
#include "registerwindow.h"
#include "loginwindow.h"

class ClientGUI : public QMainWindow
{
    Q_OBJECT

public:
    ClientGUI(QWidget *parent = nullptr);
    ~ClientGUI();

private slots:
    void on_startRegisterButton_clicked();
    void on_startLoginButton_clicked();

private:
    Ui::ClientGUIClass ui;
    RegisterWindow m_registerWindow;
    LoginWindow m_loginWindow;
};
