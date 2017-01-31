#pragma once
#include <GL/gl.h>

#include "interface/coordinates_type.h"

namespace render {


struct Vertex
{
    GLfloat position[2];
    GLfloat texture_coordinates[2];
};
struct Vertex_point
{
    Vertex_point(){};
    Vertex_point(GLfloat in_x, GLfloat in_y);
    Vertex_point(Point point);
    GLfloat position[2];
};


}
