#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include "interface/primitives/Vertex/Vertex.h"
#include "interface/View_data/View_data.h"
#include "interface/primitives/Rectangle/Rectangle.h"
#include "interface/primitives/Arrow/Arrow.h"
#include "interface/Shared_drawn_data/Shared_drawn_data.h"

namespace core {
    class Network;
    class Node;
    class Bend;
    class Hub;
}


namespace render {



class Node;
class Bend;
class Hub;

class Network_renderer: protected QOpenGLFunctions
{
public:
    Network_renderer(core::Network& in_network, QPaintDevice* paint_device);
    void initializeGL();

    void draw(const View_data& view_data);
    void draw_text_in_units(const View_data &view_data);
    void draw_unit_sprites(const View_data& view_data);
    void draw_link_lines(const View_data& view_data);
    void draw_arrows(const View_data &view_data) ;

private:
    Sprite sprite;
    Arrow arrow;

    Shared_drawn_data drawn_data;
    View_data view_data;
    QPaintDevice* paint_device;

    core::Network& network;
    
};

}
