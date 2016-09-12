//#include <QtGui/QApplication> // old qt
#include <QtWidgets/QApplication>

#include "view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    view = new View();
    view->show();
    return a.exec();
}
