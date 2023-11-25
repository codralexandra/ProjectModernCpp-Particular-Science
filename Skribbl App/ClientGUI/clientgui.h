#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_clientgui.h"

class ClientGUI : public QMainWindow
{
    Q_OBJECT

public:
    ClientGUI(QWidget *parent = nullptr);
    ~ClientGUI();

private:
    Ui::ClientGUIClass ui;
};
