#include "draw_Hub.h"

#include "interface/RenderingWidget.h"


namespace render {

Hub::Hub():
    Drawable_unit()
{

}
int Hub::get_radius()
{
    return 4;
}
QOpenGLTexture* Hub::get_texture()
{
    return renderingWidget->textures[2];
}

void Hub::update_according_to_network()
{

}

void Hub::draw()
{
    Drawable_unit::draw();
}



}
