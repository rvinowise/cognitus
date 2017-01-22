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

    //QSurfaceFormat format;
    //format.setSamples(16);

    test::Network network;
    network.init_data_for_tests();
    test::Input input(network.network);
    input.init_input_characteristics();

    //RenderingWidget renderingWindow(network.network);
    //renderingWindow.show();
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    render::RenderingWidget renderingWindow(network.network);
    renderingWindow.show();

    InterfaceWindow interfaceWindow(network.network);
    interfaceWindow.show();

    return app.exec();



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
