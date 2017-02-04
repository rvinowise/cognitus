#pragma once

#include <QtGui>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <memory>

#include "interface/coordinates_type.h"
#include "interface/primitives/Vertex/Vertex.h"


namespace render {

struct Drawable_unit_data
{
public:
    Drawable_unit_data();
    Point position;
    bool is_selected;
};

class Drawable_unit//: protected QOpenGLFunctions
{
friend class RenderingWidget;
public:
    Drawable_unit();
    Drawable_unit(Drawable_unit&& other);
    ~Drawable_unit();
    void create_data();

    void draw() const;
    void draw_link_to(const Drawable_unit& other) const;
    void draw_lines(const std::vector<Vertex_point>& vertices, const Color& color)const;

    bool is_inside(Rect rect)const;
    bool has_inside(Point point)const;
    bool is_collide(const Drawable_unit& other)const;
    void select();
    void deselect();
    bool is_selected() const;
    Point& position();

    virtual int get_radius() const;
    virtual QOpenGLTexture* get_texture() const;


private:
    Drawable_unit_data* data;

};

}
