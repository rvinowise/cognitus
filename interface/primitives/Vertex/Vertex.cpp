#include "Vertex.h"



namespace render {


Vertex_point::Vertex_point(Point point) {
    position[0] = point.x();
    position[1] = point.y();
}

Vertex_point::Vertex_point(QPointF point)
{
    position[0] = point.x();
    position[1] = point.y();
}
Vertex_point::Vertex_point(GLfloat in_x, GLfloat in_y)
{
    position[0] = in_x;
    position[1] = in_y;
}

Vertex_colored::Vertex_colored(GLfloat in_x, GLfloat in_y, Color in_color)
{
    position[0] = in_x;
    position[1] = in_y;
    //in_color.getRgbF(&color[0],&color[1],&color[2],&color[3]);
    color[0] = in_color.redF();
    color[1] = in_color.greenF();
    color[2] = in_color.blueF();
    color[3] = in_color.alphaF();
}

Vertex_colored::Vertex_colored(Point point, Color in_color)
{
    position[0] = point.x();
    position[1] = point.y();
    //in_color.getRgbF(&color[0],&color[1],&color[2],&color[3]);
    color[0] = in_color.redF();
    color[1] = in_color.greenF();
    color[2] = in_color.blueF();
    color[3] = in_color.alphaF();
}


}
