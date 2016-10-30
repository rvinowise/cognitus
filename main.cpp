#include <QtWidgets/QApplication>

#include "interface/InterfaceWindow.h"
#include "core/Network/Network.h"



#ifdef test_itself

#include "core/test/allTests.h"

using namespace test;
QTEST_MAIN(test::Network)
//QTEST_MAIN(test::Input)

#else

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Network *network = new Network();
    
    
    InterfaceWindow* interfaceWindow = new InterfaceWindow();
    interfaceWindow->show();
    return a.exec();
}


#endif
