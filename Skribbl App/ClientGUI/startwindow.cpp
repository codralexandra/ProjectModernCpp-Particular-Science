#include "startwindow.h"

StartWindow::StartWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

StartWindow::~StartWindow()
{}

void StartWindow::recievePixelFromServer()
{
}
