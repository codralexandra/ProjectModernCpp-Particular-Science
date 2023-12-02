#include "clientgui.h"
#include <QtWidgets/QApplication>
#include <qsoundeffect.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientGUI w;
    w.show();
    return a.exec();
}
