#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>


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
    void init();

    void draw();


    static QOpenGLShaderProgram shaders;
    static const std::size_t PROGRAM_VERTEX_ATTRIBUTE=0;
    static const std::size_t PROGRAM_TEXCOORD_ATTRIBUTE=1;
    static constexpr float etalon_radius = 10.0;


    static std::vector<QOpenGLTexture*> textures;
};

}
