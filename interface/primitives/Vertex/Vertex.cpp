#include "Vertex.h"



namespace render {


Vertex_point::Vertex_point(Point point) {
    position[0] = point.x();
    position[1] = point.y();
}
Vertex_point::Vertex_point(GLfloat in_x, GLfloat in_y)
{
    position[0] = in_x;
    position[1] = in_y;
}

}
