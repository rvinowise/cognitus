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
#include "interface/Text_drawer/Text_drawer.h"

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
    Network_renderer(core::Network& in_network, View_data& in_view_data, Text_drawer& in_text_drawer);
    void initializeGL();

    void draw();
    void draw_text_in_units() const;
    void draw_unit_sprites();
    void draw_link_lines();
    void draw_arrows();

private:
    void draw_text_in_node(core::Node node) const;
    void draw_text_in_bend(core::Bend bend) const;
    void draw_text_in_hub(core::Hub hub) const;
    
    Sprite sprite;
    Arrow arrow;

    Shared_drawn_data drawn_data;
    View_data& view_data;
    Text_drawer& text_drawer;

    core::Network& network;
    
};

}
