#pragma once


#include <QMainWindow>
#include <QtNetwork>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
//namespace interface {

namespace core {
    class Network;
}

namespace Ui {
class InterfaceWindow;
}

class InterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit InterfaceWindow(QWidget *parent = 0);
    InterfaceWindow(core::Network& inNetwork, QWidget *parent = 0);
    ~InterfaceWindow();

public slots:
    void on_btnStartListening_clicked();
    void processNewConnection();
    void processDisonnectionOfClient();
    void processInputFromClient();

private:
    void startListeningForConnections(int inPort);
    void outputLog(QString string);
    void outputError(QString string);

    QBitArray getArrayOfInputsFromClient(QTcpSocket* clientSocket);
    QString getErrorOfInput(QBitArray input);
    void inputToCore(const QBitArray& inputt);

    QBitArray getArrayOfOutputsFromCore();

    QTcpServer* tcpServer;
    quint16 nextBlockSize;

    Ui::InterfaceWindow *ui;

    core::Network& network;
};


//}

