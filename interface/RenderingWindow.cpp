#include "RenderingWindow.h"

#include <QDebug>
#include <QString>

#include "core/Network/Network.h"

RenderingWidget::RenderingWidget(core::Network& inNetwork):
    network(inNetwork)
{
    resize(640, 480);


}

RenderingWidget::~RenderingWidget()
{

}

void RenderingWidget::prepare_rendering_resources()
{
    static const int coords[4][2] = {
         { -1, -1}, { +1, -1}, { +1, +1}, { -1, +1 }
    };
    std::string resource_path("C:/Qt/Examples/Qt-5.7/opengl/textures/images/");
    textures.push_back(QOpenGLTexture(QImage(resource_path+"side1.png")));
    textures.push_back(QOpenGLTexture(QImage(resource_path+"side2.png")));
    textures.push_back(QOpenGLTexture(QImage(resource_path+"side3.png")));
}


void RenderingWidget::initializeGL()
{
  initializeOpenGLFunctions();
  print_context_information();



  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void RenderingWidget::resizeGL(int width, int height)
{

}

void RenderingWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
}



void RenderingWidget::print_context_information()
{
    QString glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    qDebug() << "OpenGL " << glVersion;

    GLint glParam; glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &glParam);
    qDebug() << glParam;
}
