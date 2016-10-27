#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QtNetwork>

//namespace interface {

namespace Ui {
class InterfaceWindow;
}

class InterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterfaceWindow(QWidget *parent = 0);
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
    void inputToCore(QBitArray input);

    QTcpServer* tcpServer;
    quint16 nextBlockSize;

    Ui::InterfaceWindow *ui;
};


//}

#endif // INTERFACE_H
