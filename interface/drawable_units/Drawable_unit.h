#pragma once

#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <string>
#include <glm/glm.hpp>
#include <memory>

class Drawable_unit: protected QOpenGLFunctions
{
public:
    Drawable_unit();

    void draw();
    void draw_link_to(const Drawable_unit& other);
//protected:
    QVector2D position;
    //QVector2D position;
    std::shared_ptr<QOpenGLTexture> texture;

};

