#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T01:19:53
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11

QT += widgets core gui network testlib

#CONFIG += c++11
DEFINES += test_itself debug_mode debug_msg_core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cognitus
TEMPLATE = app
#TEMPLATE=vcapp

SOURCES += main.cpp \
    core/Bend/Bend.cpp \
    core/Network/Interface/Input/Input.cpp \
    core/Network/Network.cpp \
    core/Node/Node.cpp \
    core/Network/ActiveBend/ActiveBend.cpp \
    core/Node/InterfaceNode.cpp \
    core/Bend/BendOfFigure/BendOfFigure.cpp \
    core/Bend/FreeBend/FreeBend.cpp \
    core/Circuit/Circuit.cpp \
    core/Network/Interface/Output/Output.cpp \
    interface/InterfaceWindow.cpp \
    core/threadSynchronization/WaiterForCondition.cpp \
    core/Network/Interface/Interface.cpp \
    core/Network/test/testNetwork.cpp \
    core/Network/CircuitFinder/CircuitFinder.cpp \
    core/Network/Interface/Input/test/testInput.cpp \
    core/Network/CircuitFinder/test/testCircuitFinder.cpp \
    core/test/randomFunc.cpp \
    core/test/Debug_inspector.cpp \
    core/test/Speed_profiler.cpp




HEADERS  += \
    core/Bend/Bend.h \
    core/Network/Interface/Input/Input.h \
    core/Network/Interface/Output/Output.h \
    core/Network/Interface/Interface.h \
    core/Network/Network.h \
    core/Node/Node.h \
    core/Network/ActiveBend/ActiveBend.h \
    core/Node/InterfaceNode.h \
    core/Bend/BendOfFigure/BendOfFigure.h \
    core/Bend/FreeBend/FreeBend.h \
    core/Circuit/Circuit.h \
    interface/InterfaceWindow.h \
    core/threadSynchronization/WaiterForCondition.h \
    core/Network/CircuitFinder/CircuitFinder.h \
    core/Network/Interface/Input/test/testInput.h \
    core/Network/test/testNetwork.h \
    core/test/allTests.h \
    core/Network/CircuitFinder/test/testCircuitFinder.h \
    core/test/randomFunc.h \
    core/test/Debug_inspector.h \
    core/test/Speed_profiler.h \
    core/Node/Node_data.h



FORMS    += \
    interface/InterfaceWindow.ui

INCLUDEPATH += \
    C:/ydisk/program/boost_1_62_0/
