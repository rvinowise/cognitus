#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T01:19:53
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11

QT += widgets core gui opengl network

#CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cognitus
TEMPLATE = app


SOURCES += main.cpp \
    view.cpp \
    core/Bend/Bend.cpp \
    core/Network/Interface/Input/Input.cpp \
    core/Network/Interface/interface.cpp \
    core/Network/Network.cpp \
    core/Node/Node.cpp \
    Visualisator/Visualisator.cpp \
    ../gameEngine/functions/Point/Point.cpp \
    ../gameEngine/functions/posFunctions.cpp \
    ../gameEngine/functions/random.cpp \
    ../gameEngine/spriteEngine/Frame.cpp \
    ../gameEngine/spriteEngine/Screen.cpp \
    ../gameEngine/spriteEngine/Sprite.cpp \
    ../gameEngine/spriteEngine/SpriteBase.cpp \
    ../gameEngine/spriteEngine/spriteFunctions.cpp \
    ../gameEngine/spriteEngine/SpriteView.cpp \
    sprites/spriteIndexes.cpp \
    core/Network/ActiveBend/ActiveBend.cpp \
    core/Node/InterfaceNode.cpp \
    core/Bend/BendOfFigure/BendOfFigure.cpp \
    core/Bend/FreeBend/FreeBend.cpp \
    core/Circuit/Circuit.cpp \
    core/Network/Interface/Output/Output.cpp \
    interface/InterfaceWindow.cpp \
    core/threadSynchronization/WaiterForCondition.cpp




HEADERS  += \
    core/Bend/Bend.h \
    core/Network/Interface/Input/Input.h \
    core/Network/Interface/Output/Output.h \
    core/Network/Interface/Interface.h \
    core/Network/Network.h \
    core/Node/Node.h \
    Visualisator/Visualisator.h \
    ../gameEngine/functions/Point/Point.h \
    ../gameEngine/functions/posFunctions.h \
    ../gameEngine/functions/random.h \
    ../gameEngine/spriteEngine/Frame.h \
    ../gameEngine/spriteEngine/Screen.h \
    ../gameEngine/spriteEngine/Sprite.h \
    ../gameEngine/spriteEngine/SpriteBase.h \
    ../gameEngine/spriteEngine/spriteFunctions.h \
    ../gameEngine/spriteEngine/SpriteView.h \
    view.h \
    sprites/spriteIndexes.h \
    core/Network/ActiveBend/ActiveBend.h \
    core/Node/InterfaceNode.h \
    core/Bend/BendOfFigure/BendOfFigure.h \
    core/Bend/FreeBend/FreeBend.h \
    core/Circuit/Circuit.h \
    interface/InterfaceWindow.h \
    core/threadSynchronization/WaiterForCondition.h



FORMS    += \
    interface/InterfaceWindow.ui
