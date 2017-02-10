#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/test/Debug_inspector.h"


namespace core {
    class Bend;
}

namespace render {


class Bend: public Drawable_unit
{
public:
    Bend();
    Bend(const Bend& other);
    Bend(Bend&& other);

    void draw();
    void draw_links_to_next_bends();
    Color get_links_to_next_bends_color() const;
    void draw_arrows();

    int get_radius()const;
    virtual QOpenGLTexture* get_texture()const;

    virtual std::vector<core::Bend>& get_array_of_next_bends() = 0;

private:

};


}
