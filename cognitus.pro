#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T01:19:53
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11

QT += widgets core gui network testlib opengl

#CONFIG += c++11
CONFIG += object_parallel_to_source
DEFINES += test_itself debug_mode debug_msg_core render_mode

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cognitus
TEMPLATE = app
#TEMPLATE=vcapp

SOURCES += main.cpp \
    core/auxiliary/Acquiring_handles/Acquiring_handles.cpp \
    core/Network/Circuit/Circuit.cpp \
    core/Network/CircuitFinder/test/testCircuitFinder.cpp \
    core/Network/CircuitFinder/CircuitFinder.cpp \
    core/Network/Interface/Input/test/testInput.cpp \
    core/Network/Interface/Input/Input.cpp \
    core/Network/Interface/Output/Output.cpp \
    core/Network/Interface/Interface.cpp \
    core/Network/Link/Linked.cpp \
    core/Network/Node/Bend/Bend.cpp \
    core/Network/Node/Hub/Iterator/Iterator_BFS.cpp \
    core/Network/Node/Hub/Hub.cpp \
    core/Network/Node/Iterator/Iterator_node_BFS.cpp \
    core/Network/Node/InterfaceNode.cpp \
    core/Network/Node/Node.cpp \
    core/Network/test/testNetwork.cpp \
    core/Network/Network.cpp \
    core/test/Debug_inspector.cpp \
    core/test/randomFunc.cpp \
    core/test/Speed_profiler.cpp \
    core/threadSynchronization/WaiterForCondition.cpp \
    interface/drawable_units/draw_Bend.cpp \
    interface/drawable_units/draw_Hub.cpp \
    interface/drawable_units/draw_Node.cpp \
    interface/drawable_units/Drawable_unit.cpp \
    interface/Human_control/Human_control.cpp \
    interface/primitives/Vertex/Vertex.cpp \
    interface/algorithms.cpp \
    interface/InterfaceWindow.cpp \
    interface/RenderingWidget.cpp \
    interface/primitives/Arrow/Arrow.cpp \
    interface/primitives/Rectangle/Rectangle.cpp \
    interface/functions/functions.cpp \
    interface/drawable_units/Network_renderer.cpp \
    interface/View_data/View_data.cpp \
    interface/Units_disposer/Units_disposer.cpp \
    interface/Shared_drawn_data/Shared_drawn_data.cpp \
    core/Network/Synchro_bends/Synchro_bends.cpp





HEADERS  += \
    core/auxiliary/Acquiring_handles/Acquiring_handles.h \
    core/Network/Circuit/Circuit.h \
    core/Network/CircuitFinder/test/testCircuitFinder.h \
    core/Network/CircuitFinder/CircuitFinder.h \
    core/Network/Interface/Input/test/testInput.h \
    core/Network/Interface/Input/Input.h \
    core/Network/Interface/Output/Output.h \
    core/Network/Interface/Interface.h \
    core/Network/Link/Linked.h \
    core/Network/Node/Bend/Bend.h \
    core/Network/Node/Bend/Bend_data.h \
    core/Network/Node/Hub/Iterator/Iterator_BFS.h \
    core/Network/Node/Hub/Hub.h \
    core/Network/Node/Hub/Hub_data.h \
    core/Network/Node/Iterator/Iterator_node_BFS.h \
    core/Network/Node/InterfaceNode.h \
    core/Network/Node/Node.h \
    core/Network/Node/Node_data.h \
    core/Network/test/testNetwork.h \
    core/Network/Network.h \
    core/test/allTests.h \
    core/test/Debug_inspector.h \
    core/test/randomFunc.h \
    core/test/Speed_profiler.h \
    core/threadSynchronization/WaiterForCondition.h \
    interface/drawable_units/draw_Bend.h \
    interface/drawable_units/draw_Hub.h \
    interface/drawable_units/draw_Node.h \
    interface/drawable_units/Drawable_unit.h \
    interface/functions/functions.h \
    interface/Human_control/Human_control.h \
    interface/primitives/Vertex/Vertex.h \
    interface/algorithms.h \
    interface/coordinates_type.h \
    interface/InterfaceWindow.h \
    interface/RenderingWidget.h \
    interface/primitives/Arrow/Arrow.h \
    interface/primitives/Rectangle/Rectangle.h \
    interface/common/constants.h \
    interface/common/coordinates_type.h \
    interface/drawable_units/Network_renderer.h \
    interface/View_data/View_data.h \
    interface/Units_disposer/Units_disposer.h \
    interface/Shared_drawn_data/Shared_drawn_data.h \
    core/Network/Synchro_bends/Synchro_bends.h




FORMS    += \
    interface/InterfaceWindow.ui

INCLUDEPATH += \
    C:/ydisk/program/boost_1_62_0/ \
    D:/program/glm/

#DISTFILES += \
#    interface/shaders/sprite.frag \
#    interface/shaders/sprite.vert

DISTFILES += \
    core/Network/Node/Bend/position.JPG \
    core/Network/Node/Hub/position2.png \
    core/Network/Interface/info.rus \
    interface/sprites/old/bend.png \
    interface/sprites/old/hub.png \
    interface/sprites/old/node — копия (2).png \
    interface/sprites/old/node — копия.png \
    interface/sprites/bend.png \
    interface/sprites/hub.png \
    interface/sprites/node.png \
    interface/shaders/old/sprite.frag \
    interface/shaders/selection.frag \
    interface/shaders/sprite.frag \
    interface/shaders/selection.vert \
    interface/shaders/sprite.vert
