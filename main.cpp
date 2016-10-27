//#include <QtGui/QApplication> // old qt
#include <QtWidgets/QApplication>

//#include "view.h"
#include "interface/InterfaceWindow.h"
#include "core/Network/Network.h"

//using namespace interface;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Network *network = new Network();
    
    
    InterfaceWindow* interfaceWindow = new InterfaceWindow();
    interfaceWindow->show();
    return a.exec();
}
