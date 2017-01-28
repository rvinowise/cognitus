#pragma once

#include <QtGui>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <memory>

namespace render {

using Point = QPoint;
using Rect = QRect;

class Drawable_unit: protected QOpenGLFunctions
{
friend class RenderingWidget;
public:
    Drawable_unit();

    void draw();
    void draw_link_to(const Drawable_unit& other);

    bool is_inside(Rect rect);
    bool has_inside(Point point);
    bool is_collide(const Drawable_unit& other);
    void select();
    void deselect();

    Point position;
 protected:
    bool is_selected;
    int radius;

    QOpenGLTexture* texture;

};

}
