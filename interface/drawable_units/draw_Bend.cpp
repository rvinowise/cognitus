#include "draw_Bend.h"

#include "interface/RenderingWidget.h"


namespace render {

Bend::Bend():
    Drawable_unit()
{

}

int Bend::get_radius() const
{
    return 3;
}
QOpenGLTexture* Bend::get_texture() const
{
    return renderingWidget->textures[1];
}

bool Bend::operator ==(const core::Bend &real_bend) const
{
    return (this->bend == real_bend);
}

void Bend::draw() const
{
    Drawable_unit::draw();
}



}
