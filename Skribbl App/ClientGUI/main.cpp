#include "clientgui.h"
#include <QtWidgets/QApplication>
#include <qsoundeffect.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSoundEffect* sound = new QSoundEffect;
    sound->setVolume(10);
    sound->setSource(QUrl::fromLocalFile("E:\Scoala\Facultate\An2\ModernC++\Proiect\Coding\ProjectModernCpp-Particular-Science\Skribbl App\ClientGUI\Sounds\MainMenu.mp3"));
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->play();
    ClientGUI w;
    w.show();
    return a.exec();
}
