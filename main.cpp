#include "mainwidget.h"
#include <QApplication>

#include "makedesktop.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwidget w;
    makeDesktop::setStartUpAutoRun();
    makeDesktop::MakeHandleDesktop(&w);
    w.show();

    return a.exec();
}
