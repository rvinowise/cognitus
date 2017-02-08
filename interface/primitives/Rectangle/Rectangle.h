#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>


#include "interface/primitives/Vertex/Vertex.h"



namespace render {


class Rectangle
{
public:
    Rectangle();

    static void init();


    static QOpenGLVertexArrayObject vao_rect;
    static QOpenGLBuffer vertex_buffer;


};

class Sprite: protected QOpenGLFunctions
{
public:
    Sprite();
    static void init();
    static void draw();

    static QOpenGLShaderProgram shaders;
    static const std::size_t PROGRAM_VERTEX_ATTRIBUTE=0;
    static const std::size_t PROGRAM_TEXCOORD_ATTRIBUTE=1;
};

}
