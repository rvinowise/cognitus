/********************************************************************************
** Form generated from reading UI file 'InterfaceWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
    QLabel *label;
    QLineEdit *edInputSize;
    QLabel *label_2;
    QPlainTextEdit *edLog;
    QLineEdit *edOutputSize;
    QPushButton *btnStartListening;
    QLineEdit *edPort;
    QGridLayout *layRendering;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InterfaceWindow)
    {
        if (InterfaceWindow->objectName().isEmpty())
            InterfaceWindow->setObjectName(QStringLiteral("InterfaceWindow"));
        InterfaceWindow->resize(800, 601);
        centralwidget = new QWidget(InterfaceWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        edInputSize = new QLineEdit(centralwidget);
        edInputSize->setObjectName(QStringLiteral("edInputSize"));

        gridLayout->addWidget(edInputSize, 0, 3, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 4, 1, 1);

        edLog = new QPlainTextEdit(centralwidget);
        edLog->setObjectName(QStringLiteral("edLog"));

        gridLayout->addWidget(edLog, 1, 0, 1, 6);

        edOutputSize = new QLineEdit(centralwidget);
        edOutputSize->setObjectName(QStringLiteral("edOutputSize"));

        gridLayout->addWidget(edOutputSize, 0, 5, 1, 1);

        btnStartListening = new QPushButton(centralwidget);
        btnStartListening->setObjectName(QStringLiteral("btnStartListening"));

        gridLayout->addWidget(btnStartListening, 0, 0, 1, 1);

        edPort = new QLineEdit(centralwidget);
        edPort->setObjectName(QStringLiteral("edPort"));

        gridLayout->addWidget(edPort, 0, 1, 1, 1);

        layRendering = new QGridLayout();
        layRendering->setSpacing(10);
        layRendering->setObjectName(QStringLiteral("layRendering"));
        layRendering->setContentsMargins(100, 100, 100, 100);

        gridLayout->addLayout(layRendering, 2, 0, 1, 1);

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
        InterfaceWindow->setWindowTitle(QApplication::translate("InterfaceWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("InterfaceWindow", "inputs", Q_NULLPTR));
        label_2->setText(QApplication::translate("InterfaceWindow", "outputs", Q_NULLPTR));
        btnStartListening->setText(QApplication::translate("InterfaceWindow", "go listen", Q_NULLPTR));
        edPort->setText(QApplication::translate("InterfaceWindow", "99", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InterfaceWindow: public Ui_InterfaceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEWINDOW_H
