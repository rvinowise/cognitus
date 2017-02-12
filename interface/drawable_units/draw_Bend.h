#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/test/Debug_inspector.h"
#include "interface/View_data/View_data.h"
#include "interface/Shared_drawn_data/Shared_drawn_data.h"

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

    void prepare_draw_data(Shared_drawn_data& drawn_data)const;

    static const float radius;
    int get_radius()const;
    static QOpenGLTexture* get_texture();

    virtual std::vector<core::Bend>& get_array_of_next_bends() = 0;
    virtual const std::vector<core::Bend>& get_array_of_next_bends()const = 0;

private:

};


}
