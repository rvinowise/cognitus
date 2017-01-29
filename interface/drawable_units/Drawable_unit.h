#pragma once

#include <QtGui>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <memory>

#include "interface/coordinates_type.h"


namespace render {



class Drawable_unit//: protected QOpenGLFunctions
{
friend class RenderingWidget;
public:
    Drawable_unit();
    virtual void update_according_to_network(){};

    void draw();
    void draw_link_to(const Drawable_unit& other);

    bool is_inside(Rect rect);
    bool has_inside(Point point);
    bool is_collide(const Drawable_unit& other);
    void select();
    void deselect();

    virtual int get_radius(){};
    virtual QOpenGLTexture* get_texture(){};
    Point position;


 protected:
    bool is_selected;

};

}
