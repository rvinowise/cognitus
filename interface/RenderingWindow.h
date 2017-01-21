#pragma once

#include <QtGui>
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
namespace core {
    class Network;
}

class RenderingWidget: public QOpenGLWidget,
                        protected QOpenGLFunctions
{
public:
    RenderingWidget(core::Network &rendering_network);
    ~RenderingWidget();

    void prepare_rendering_resources();
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
    void print_context_information();

    std::vector<QOpenGLTexture> textures;
    QOpenGLShader vertex_shader;
    QOpenGLShader fragment_shader;
    QOpenGLShaderProgram shader_program;
    QOpenGLBuffer vertex_buffer;


    core::Network& network;


};


