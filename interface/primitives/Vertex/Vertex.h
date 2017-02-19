#pragma once
#include <GL/gl.h>

#include "interface/common/constants.h"

namespace render {

struct Vertex_point
{
    Vertex_point(){}
    Vertex_point(GLfloat in_x, GLfloat in_y);
    Vertex_point(Point point);
    Vertex_point(QPointF point);
    GLfloat position[2];
};

struct Vertex
{
    Vertex() = default;
    Vertex(Vertex_point in_point):position{in_point.position[0], in_point.position[1]}{}
    Vertex(Vertex_point in_point, GLfloat tex_x, GLfloat tex_y):
        position{in_point.position[0], in_point.position[1]}, texture_coordinates{tex_x, tex_y} {}
    Vertex(Point in_point, GLfloat tex_x, GLfloat tex_y):
        position{in_point.x(), in_point.y()}, texture_coordinates{tex_x, tex_y} {}
    GLfloat position[2];
    GLfloat texture_coordinates[2];
};

struct Vertex_colored
{
    Vertex_colored(){}
    Vertex_colored(GLfloat in_x, GLfloat in_y, Color in_color);
    Vertex_colored(Point point, Color in_color);
    GLfloat position[2];
    GLfloat color[4];
};


}
