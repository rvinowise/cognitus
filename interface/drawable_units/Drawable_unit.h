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
public:
    Drawable_unit();

    void draw();
    void draw_link_to(const Drawable_unit& other);

    bool is_inside(Rect rect);
    bool is_collide(const Drawable_unit& other);
//protected:
    Point position;
    bool is_selected;

    QOpenGLTexture* texture;

};

}
