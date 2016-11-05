#include <QtWidgets/QApplication>

#include "interface/InterfaceWindow.h"
#include "core/Network/Network.h"



#ifdef test_itself

#include "core/test/allTests.h"
#include "core/test/debugStuff.h"

using namespace test;
//QTEST_MAIN(test::Network)

int main()
{
    test::Network network;
    network.init_data_for_tests();
    network.work_of_network();
    debug.writeResume();
}


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
