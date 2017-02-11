#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include "interface/primitives/Vertex/Vertex.h"



namespace render {


struct Arrow_vector
{
    Point position;
    float direction;
};

struct Arrow: protected QOpenGLFunctions
{
public:
    Arrow();
    void init();

    void draw();

    static QOpenGLShaderProgram shaders;
    static QOpenGLVertexArrayObject vertex_array;
    static QOpenGLBuffer vertex_buffer;
};

}
