#pragma once

#include <QtGui>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <memory>

#include "interface/coordinates_type.h"
#include "interface/primitives/Vertex/Vertex.h"


namespace render {



class Drawable_unit//: protected QOpenGLFunctions
{
friend class RenderingWidget;
public:
    Drawable_unit();
    virtual void update_according_to_network(){};

    void draw() const;
    void draw_link_to(const Drawable_unit& other) const;
    void draw_link_lines(const std::vector<Vertex_point>& vertices, const Color& color)const;

    bool is_inside(Rect rect)const;
    bool has_inside(Point point)const;
    bool is_collide(const Drawable_unit& other)const;
    void select();
    void deselect();

    virtual int get_radius()const{};
    virtual QOpenGLTexture* get_texture()const{};
    Point position;


 protected:
    bool is_selected;

private:


};

}
