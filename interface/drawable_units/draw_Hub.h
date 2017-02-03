#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/Network/Node/Hub/Hub.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"

namespace render {

class Node;

class Hub: public Drawable_unit
{
public:
    Hub();

    void draw() const;

    int get_radius()const;
    QOpenGLTexture* get_texture() const;
    Color get_links_to_next_hubs_color() const;

//private:
    void draw_links_to_next_hubs() const;

};

}

