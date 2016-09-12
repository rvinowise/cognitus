#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T01:19:53
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x

QT += widgets core gui opengl

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
    core/Node/InterfaceNode.cpp




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
    core/Network/Activity/ActiveBend.h \
    core/Network/ActiveBend/ActiveBend.h \
    core/Node/InterfaceNode.h



FORMS    += mainwindow.ui
