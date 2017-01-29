#include "draw_Bend.h"

#include "interface/RenderingWidget.h"


namespace render {

Bend::Bend():
    Drawable_unit()
{

}

int Bend::get_radius()
{
    return 3;
}
QOpenGLTexture* Bend::get_texture()
{
    return renderingWidget->textures[1];
}

void Bend::draw()
{
    Drawable_unit::draw();
}



}
