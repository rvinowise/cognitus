#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"

namespace core {
    class Hub;
}

namespace render {

class Node;

class Hub: public Drawable_unit
{
public:
    Hub();
    Hub(const Hub& other);
    Hub(Hub&& other);

    void draw() const;

    int get_radius()const;
    QOpenGLTexture* get_texture() const;
    Color get_links_to_next_hubs_color() const;

    virtual std::vector<core::Hub>& get_arr_next_hubs() const = 0;

private:

    void draw_links_to_next_hubs() const;

};

}

