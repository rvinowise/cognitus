#pragma once

#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <string>
#include <memory>

#include "drawable_units/draw_Node.h"
#include "interface/Human_control/Human_control.h"
#include "interface/coordinates_type.h"

namespace core {
    class Network;
}

namespace render {


class RenderingWidget: public QOpenGLWidget,
                        protected QOpenGLFunctions
{
public:
    explicit RenderingWidget(core::Network &rendering_network, QWidget *parent = 0);
    //explicit RenderingWidget(RenderingWidget* other = 0);
    ~RenderingWidget();

    static const QString resource_path;
    QMatrix4x4 projection_matrix;
    QOpenGLShaderProgram shader_program;
    QOpenGLShaderProgram shaders_selection;
    static const std::size_t PROGRAM_VERTEX_ATTRIBUTE=0;
    static const std::size_t PROGRAM_TEXCOORD_ATTRIBUTE=1;
    static constexpr GLfloat sprite_etalon_radius = 10;

    void draw_unit_rect();
    void draw_selection_rect();
    Rect window_rect;
    float window_scale;
    std::vector<QOpenGLTexture*> textures;
    void update_selection_rect();
    QOpenGLBuffer vertex_buffer;
    QOpenGLVertexArrayObject vao_sprite_rect;
    std::vector<Node> units;

protected:

    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent*event) Q_DECL_OVERRIDE;

private:
    void initialize_units();
    void update_units_according_to_network();
    void prepare_rendering_resources();
    void prepare_graphic_settings();
    void print_context_information();




    QColor clear_color;

    Human_control human_control;


    //std::map<core::>
    core::Network& network;


};

extern RenderingWidget* renderingWidget;

struct Vertex
{
    GLfloat position[2];
    GLfloat texture_coordinates[2];
};

}
