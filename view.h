#pragma once

#include <QGLWidget>
#include <QtOpenGL>

#include <QMouseEvent>

#include "Visualisator/Visualisator.h"
#include "../gameEngine/spriteEngine/SpriteView.h"


class View : public QGLWidget
{
    Q_OBJECT
public slots:
    void stepTimer();
public:
    View(QWidget *parent = 0);

    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int inWidth, int inHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран

    void mouseMoveEvent(QMouseEvent* mouseEvent);
    void mousePressEvent(QMouseEvent* mouseEvent);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

    QTimer timer;

    float VIRTUAL_HEIGHT;
    float VIRTUAL_WIDTH;
    float ASPECT_RATIO;
    float scale; // viewport size
    float aspectRatio;

    Visualisator visualisator;

};

extern View* view;

