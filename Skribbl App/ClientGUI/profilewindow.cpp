#include "profilewindow.h"

profileWindow::profileWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(ui.historyList);
}

profileWindow::~profileWindow()
{}

void profileWindow::on_refreshHistoryButton_clicked()
{
	//req from server
	//get json 
	//unpack and addItem to historyList
}
