#pragma once

#include <QtGui>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <memory>

#include "interface/common/constants.h"
#include "interface/primitives/Vertex/Vertex.h"
#include "interface/View_data/View_data.h"


namespace core {
    class Bend;
    class Node;
    class Hub;
}
namespace render {

class Node;
class Bend;
class Hub;
class Sprite;

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
    Drawable_unit& operator=(const Drawable_unit& other);

    Drawable_unit get_empty();

    bool is_empty() const;
    bool exists() const;

    void prepare_shader_for_drawing
    (const QMatrix4x4& projection_matrix, QOpenGLShaderProgram &shaders) const;

    void draw(const View_data &view_data, Sprite &sprite) const;

    bool is_inside(Rect rect)const;
    bool has_inside(Point point)const;
    bool is_collide(const Drawable_unit& other)const;
    void select();
    void deselect();
    bool is_selected() const;
    Point& position();
    Point position() const;

    virtual int get_radius()const;

private:
    Drawable_unit_data* data;

};

}
