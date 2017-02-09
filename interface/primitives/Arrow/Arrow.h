#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include "interface/primitives/Vertex/Vertex.h"



namespace render {


struct Arrow: protected QOpenGLFunctions
{
public:
    Arrow();

    static void init();
    static void draw();

    static QOpenGLShaderProgram shaders;
    static QOpenGLVertexArrayObject vertex_array;
    static QOpenGLBuffer vertex_buffer;
};

}
