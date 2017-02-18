#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "interface/View_data/View_data.h"


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

    void prepare_draw_data(std::vector<Vertex_colored> &vertices) const;

    static const float radius;
    int get_radius()const;
    static QOpenGLTexture* get_texture();
    Color get_links_to_next_hubs_color() const;

    virtual std::vector<core::Hub>& get_arr_next_hubs() const = 0;
    virtual std::vector<core::Bend>& bends() const = 0;

private:


};

}

