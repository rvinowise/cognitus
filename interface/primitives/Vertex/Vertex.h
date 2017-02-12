#pragma once
#include <GL/gl.h>

#include "interface/common/constants.h"

namespace render {


struct Vertex
{
    GLfloat position[2];
    GLfloat texture_coordinates[2];
};
struct Vertex_point
{
    Vertex_point(){}
    Vertex_point(GLfloat in_x, GLfloat in_y);
    Vertex_point(Point point);
    Vertex_point(QPointF point);
    GLfloat position[2];
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
