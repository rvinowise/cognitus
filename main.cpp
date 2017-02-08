#include <QtWidgets/QApplication>
#include <QGuiApplication>

#include "interface/InterfaceWindow.h"
#include "interface/RenderingWidget.h"
#include "core/Network/Network.h"



#ifdef test_itself

#include "core/test/allTests.h"
#include "core/test/Debug_inspector.h"

using namespace test;

int main(int argc, char *argv[])
{
    QApplication  app(argc, argv);

    core::Network network;
    test::Network test_network(network);
    test_network.init_common_data_for_all_tests();
    test::Input input(network);
    //input.init_input_characteristics();


    render::RenderingWidget renderingWindow(network);
    renderingWindow.show();

    InterfaceWindow interfaceWindow(network);
    interfaceWindow.show();

    return app.exec();


    //test_network.work_of_network();
    //debug.write_resume();
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
