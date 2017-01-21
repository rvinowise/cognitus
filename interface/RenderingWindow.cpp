#include "RenderingWindow.h"

#include <QDebug>
#include <QString>

#include "core/Network/Network.h"

RenderingWidget::RenderingWidget(core::Network& rendering_network):
    network(rendering_network),
    vertex_shader(QOpenGLShader::Vertex),
    fragment_shader(QOpenGLShader::Fragment)
{
    resize(640, 480);
    prepare_rendering_resources();

}

RenderingWidget::~RenderingWidget()
{

}

void RenderingWidget::prepare_rendering_resources()
{
    static const int sprite_coordinates[4][2] = {
         { -1, -1}, { +1, -1}, { +1, +1}, { -1, +1 }
    };
    std::string resource_path("C:/Qt/Examples/Qt-5.7/opengl/textures/images/");
    textures.push_back(QOpenGLTexture(QImage(resource_path+"side1.png")));
    textures.push_back(QOpenGLTexture(QImage(resource_path+"side2.png")));
    textures.push_back(QOpenGLTexture(QImage(resource_path+"side3.png")));

    vertex_shader.compileSourceFile("/home/v/ydisk/program/textures/shader.vert");
    fragment_shader.compileSourceFile("/home/v/ydisk/program/textures/shader.frag");

    program.addShader(vertex_shader);
    program.addShader(fragment_shader);
    program.bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program.bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program.link();

    program->bind();
    program->setUniformValue("texture", 0);
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
