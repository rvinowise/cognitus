#pragma once

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "interface/primitives/Vertex/Vertex.h"
#include "interface/primitives/Arrow/Arrow.h"


namespace render {

struct Shared_drawn_data
{
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer buffer;
    QOpenGLShaderProgram shaders;
    std::vector<Vertex_colored> vertices;
    std::vector<Arrow_vector> arrow_vectors;
    std::vector<Vertex_point> arrow_vertices;
};



}
