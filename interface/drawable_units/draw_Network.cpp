#include "draw_Network.h"

#include "core/Network/Network.h"

namespace render {



Network::Network()
{

}

void Network::draw()
{
    //Rectangle::vao_rect.bind();
    //Sprite::shaders.bind();
    //render::Node::get_texture()->bind();
    for (core::Node node: network) {
        node.draw();
    }
    /*render::Bend::get_texture()->bind();
    for (core::Node node: network) {
        for (core::Bend bend: node.bends())
            bend.draw();
    }
    render::Hub::get_texture()->bind();
    for (core::Node node: network) {
        for (core::Hub hub: node)
            hub.draw();
    }*/
}



}
