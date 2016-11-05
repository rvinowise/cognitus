/********************************************************************************
** Form generated from reading UI file 'InterfaceWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEWINDOW_H
#define UI_INTERFACEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLineEdit *edInputSize;
    QLineEdit *edOutputSize;
    QLabel *label;
    QPushButton *btnStartListening;
    QLineEdit *edPort;
    QLabel *label_2;
    QPlainTextEdit *edLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InterfaceWindow)
    {
        if (InterfaceWindow->objectName().isEmpty())
            InterfaceWindow->setObjectName(QStringLiteral("InterfaceWindow"));
        InterfaceWindow->resize(800, 600);
        centralwidget = new QWidget(InterfaceWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        edInputSize = new QLineEdit(centralwidget);
        edInputSize->setObjectName(QStringLiteral("edInputSize"));

        gridLayout->addWidget(edInputSize, 0, 4, 1, 1);

        edOutputSize = new QLineEdit(centralwidget);
        edOutputSize->setObjectName(QStringLiteral("edOutputSize"));

        gridLayout->addWidget(edOutputSize, 0, 6, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 3, 1, 1);

        btnStartListening = new QPushButton(centralwidget);
        btnStartListening->setObjectName(QStringLiteral("btnStartListening"));

        gridLayout->addWidget(btnStartListening, 0, 0, 1, 1);

        edPort = new QLineEdit(centralwidget);
        edPort->setObjectName(QStringLiteral("edPort"));

        gridLayout->addWidget(edPort, 0, 2, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 5, 1, 1);

        edLog = new QPlainTextEdit(centralwidget);
        edLog->setObjectName(QStringLiteral("edLog"));

        gridLayout->addWidget(edLog, 1, 0, 1, 7);

        InterfaceWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InterfaceWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        InterfaceWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(InterfaceWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        InterfaceWindow->setStatusBar(statusbar);

        retranslateUi(InterfaceWindow);

        QMetaObject::connectSlotsByName(InterfaceWindow);
    } // setupUi

    void retranslateUi(QMainWindow *InterfaceWindow)
    {
        InterfaceWindow->setWindowTitle(QApplication::translate("InterfaceWindow", "MainWindow", 0));
        label->setText(QApplication::translate("InterfaceWindow", "inputs", 0));
        btnStartListening->setText(QApplication::translate("InterfaceWindow", "go listen", 0));
        edPort->setText(QApplication::translate("InterfaceWindow", "99", 0));
        label_2->setText(QApplication::translate("InterfaceWindow", "outputs", 0));
    } // retranslateUi

};

namespace Ui {
    class InterfaceWindow: public Ui_InterfaceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEWINDOW_H
