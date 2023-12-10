#pragma once

#include <QWidget>
#include "ui_userwindow.h"

class UserWindow : public QWidget
{
	Q_OBJECT

public:
	UserWindow(QWidget *parent = nullptr);
	~UserWindow();

private:
	Ui::UserWindowClass ui;
};
