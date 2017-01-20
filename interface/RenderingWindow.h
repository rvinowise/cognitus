#pragma once

#include <QtGui>
#include <QOpenGLWindow>
#include <QOpenGLFunctions>

class RenderingWindow: public QOpenGLWindow,
                        protected QOpenGLFunctions
{
    //Q_OBJECT
public:
    RenderingWindow();
    ~RenderingWindow();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    /*void paintUnderGL() {}
    void paintOverGL() {}

    void paintEvent(QPaintEvent *event) {}
    void resizeEvent(QResizeEvent *event) {}
    int metric(PaintDeviceMetric metric) const {}
    QPaintDevice *redirected(QPoint *) const {}*/

private:
    void printContextInformation();

};


