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

    void initializeGL(); // ����� ��� ����������������� opengl
    void resizeGL(int inWidth, int inHeight); // ����� ���������� ����� ������� ��������� ������� ����
    void paintGL(); // ����� ��� ������ ����������� �� �����

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

