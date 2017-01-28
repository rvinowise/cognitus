#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T01:19:53
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11

QT += widgets core gui network testlib opengl

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
    core/test/Speed_profiler.cpp \
    core/Bend/Link/Link.cpp \
    core/auxiliary/Acquiring_handles/Acquiring_handles.cpp \
    core/Bend/Figure_bend/Figure_bend.cpp \
    core/Bend/Figure_bend/Iterator/Iterator_BFS.cpp \
    interface/RenderingWidget.cpp \
    interface/drawable_units/Drawable_unit.cpp \
    interface/drawable_units/draw_Bend.cpp \
    interface/drawable_units/draw_Hub.cpp \
    interface/drawable_units/draw_Node.cpp \
    interface/Human_control/Human_control.cpp




HEADERS  += \
    core/Bend/Bend.h \
    core/Network/Interface/Input/Input.h \
    core/Network/Interface/Output/Output.h \
    core/Network/Interface/Interface.h \
    core/Network/Network.h \
    core/Node/Node.h \
    core/Network/ActiveBend/ActiveBend.h \
    core/Node/InterfaceNode.h \
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
    core/Node/Node_data.h \
    core/Bend/FreeBend/Free_bend.h \
    core/auxiliary/Acquiring_handles/Acquiring_handles.h \
    core/Bend/Link/Linked.h \
    core/Bend/Figure_bend/Figure_bend.h \
    core/Bend/Figure_bend/Figure_bend_data.h \
    core/Bend/Bend_data.h \
    core/Bend/Figure_bend/Iterator/Iterator_BFS.h \
    interface/RenderingWidget.h \
    interface/drawable_units/Drawable_unit.h \
    interface/drawable_units/draw_Bend.h \
    interface/drawable_units/draw_Hub.h \
    interface/drawable_units/draw_Node.h \
    interface/Human_control/Human_control.h \
    interface/functions/functions.h



FORMS    += \
    interface/InterfaceWindow.ui

INCLUDEPATH += \
    C:/ydisk/program/boost_1_62_0/ \
    D:/program/glm/

#DISTFILES += \
#    interface/shaders/sprite.frag \
#    interface/shaders/sprite.vert
