#pragma once

#include <QWidget>
#include "ui_profilewindow.h"
#include <QScrollArea>

class profileWindow : public QWidget
{
	Q_OBJECT

public:
	profileWindow(QWidget *parent = nullptr);
	~profileWindow();
public slots:
	void on_refreshHistoryButton_clicked();

private:
	Ui::profileWindowClass ui;
};
