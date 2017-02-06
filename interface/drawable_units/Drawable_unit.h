#pragma once

#include <QtGui>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <memory>

#include "interface/coordinates_type.h"
#include "interface/primitives/Vertex/Vertex.h"

namespace core {
    class Bend;
    class Node;
    class Hub;
}
namespace render {

class Node;
class Bend;
class Hub;

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
friend class render::Node;
friend class render::Bend;
friend class render::Hub;
friend class core::Node;
friend class core::Bend;
friend class core::Hub;
public:
    Drawable_unit();
    Drawable_unit(const Drawable_unit& other);
    Drawable_unit(Drawable_unit&& other);
    ~Drawable_unit();
    void create_data();

    bool operator==(const Drawable_unit& other)const;
    bool operator=(const Drawable_unit& other);

    static Drawable_unit get_empty();
    bool is_empty() const;
    bool exists() const;

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
    Point position() const;

    virtual int get_radius() const;
    virtual QOpenGLTexture* get_texture() const;

private:
    Drawable_unit_data* data;

};

}
