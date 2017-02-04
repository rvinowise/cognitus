#pragma once

#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <string>
#include <memory>

#include "interface/Human_control/Human_control.h"
#include "interface/coordinates_type.h"

namespace core {
    class Network;
    class Node;
}

namespace render {


class RenderingWidget: public QOpenGLWidget,
                        protected QOpenGLFunctions
{
    friend class Human_control;
public:
    explicit RenderingWidget(core::Network &rendering_network, QWidget *parent = 0);
    //explicit RenderingWidget(RenderingWidget* other = 0);
    ~RenderingWidget();

    void draw_unit_rect();
    void draw_lines(std::size_t qty);

    static const QString resource_path;
    QMatrix4x4 projection_matrix;
    QOpenGLShaderProgram shaders_sprite;
    static const std::size_t PROGRAM_VERTEX_ATTRIBUTE=0;
    static const std::size_t PROGRAM_TEXCOORD_ATTRIBUTE=1;
    static constexpr GLfloat sprite_etalon_radius = 10;
    QOpenGLShaderProgram shaders_link_lines;



    Rect window_rect;
    float window_scale;
    std::vector<QOpenGLTexture*> textures;

    QOpenGLBuffer vertex_buffer;
    QOpenGLVertexArrayObject vao_sprite_rect;
    QOpenGLBuffer link_lines_buffer;
    QOpenGLVertexArrayObject vao_link_lines;


protected:

    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent*event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent*event) Q_DECL_OVERRIDE;

private:
    void initialize_units();
    void update_units_according_to_network();
    void prepare_rendering_resources();
    void prepare_graphic_settings();
    void print_context_information();

    QColor clear_color;

    Human_control human_control;


    core::Network& network;

};

extern RenderingWidget* renderingWidget;



}
