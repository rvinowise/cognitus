#include <QtWidgets/QApplication>
#include <QGuiApplication>

#include "interface/InterfaceWindow.h"
#include "interface/RenderingWindow.h"
#include "core/Network/Network.h"



#ifdef test_itself

#include "core/test/allTests.h"
#include "core/test/Debug_inspector.h"

using namespace test;

int main(int argc, char *argv[])
{
    QApplication  app(argc, argv);

    //QSurfaceFormat format;
    //format.setSamples(16);

    RenderingWindow renderingWindow;
    //renderingWindow.setFormat(format);
    //renderingWindow.resize(640, 480);
    renderingWindow.show();

    return app.exec();


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
