#include "InterfaceWindow.h"
#include "ui_InterfaceWindow.h"
//using namespace interface;
#include "core/Network/network.h"

using namespace core;

InterfaceWindow::InterfaceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterfaceWindow)
{
    ui->setupUi(this);

    nextBlockSize = 0;

    network->input.initNodes(40);
    network->output.initNodes(40);
}

InterfaceWindow::~InterfaceWindow()
{
    delete ui;
}

void InterfaceWindow::outputLog(QString string)
{
    ui->edLog->appendPlainText(string);
}

void InterfaceWindow::outputError(QString string)
{
    ui->edLog->appendPlainText(string);
}

void InterfaceWindow::on_btnStartListening_clicked()
{
    int port = ui->edPort->text().toInt();
    startListeningForConnections(port);
}


void InterfaceWindow::startListeningForConnections(int inPort)
{

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, inPort)) {
        ui->edLog->appendPlainText(
                    "Server Error: Unable to start the server:"
                    + tcpServer->errorString()
                    );
        tcpServer->close();
        return;
    }
    connect(tcpServer, SIGNAL(newConnection()),
            this, SLOT(processNewConnection())
           );
}


void InterfaceWindow::processNewConnection()
{
    QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()),
            clientSocket, SLOT(processDisonnectionOfClient())
           );
    connect(clientSocket, SIGNAL(readyRead()),
            this,          SLOT(processInputFromClient())
           );

    //sendToClient(clientSocket, "Server Response: Connected!");
    outputLog(QString("client is connected: %1:%2").arg(
                  clientSocket->peerAddress().toString()).arg(
                  clientSocket->peerPort()));
}

void InterfaceWindow::processDisonnectionOfClient()
{
    //QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());
    clientSocket->deleteLater();
    outputLog(QString("client is disconnected: %1:%2").arg(
                  clientSocket->peerAddress().toString()).arg(
                  clientSocket->peerPort()));
}

void InterfaceWindow::processInputFromClient()
{
    QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());
    QBitArray inputFromClient = getArrayOfInputsFromClient(clientSocket);
    QString errorOfInput = getErrorOfInput(inputFromClient);
    if (errorOfInput.isEmpty()) {
        inputToCore(inputFromClient);
    } else {
        outputError(errorOfInput);
    }
}

QBitArray InterfaceWindow::getArrayOfInputsFromClient(QTcpSocket* clientSocket) {
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    QBitArray arrBit;
    while(true) {
        if (!nextBlockSize) {
            if (clientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (clientSocket->bytesAvailable() < nextBlockSize) {
            break;
        }
        in >> arrBit;

        nextBlockSize = 0;
    }

    return arrBit;
}

QString InterfaceWindow::getErrorOfInput(QBitArray input) {
    if (input.size() != network->input.getNodesQty()) {
        return QString("wrong input size: client sent %1, but core needs %2")
                    .arg(input.size()).arg(network->input.getNodesQty());
    }
    return QString();
}

void InterfaceWindow::inputToCore(QBitArray input) {
    network->input.beginSettingInputFromOutside();
    for (uint i_input = 0; i_input < network->input.getNodesQty(); i_input++) {
        if (input.testBit(i_input)) {
            network->input.prepareToFire(i_input);
        }
    }
#ifndef debug_mode
    network->input.endSettingInputFromOutside();
#endif

}
