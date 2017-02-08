#include "RenderingWidget.h"

#include <QDebug>
#include <QString>

#include "core/Network/Network.h"
#include "core/Network/Node/Iterator/Iterator_node_BFS.h"
#include "interface/drawable_units/draw_Node.h"
#include "interface/primitives/Vertex/Vertex.h"
#include "algorithms.h"
#include "core/test/Debug_inspector.h"
#include "interface/primitives/Arrow/Arrow.h"
#include "interface/primitives/Rectangle/Rectangle.h"

namespace render {




RenderingWidget* renderingWidget;





RenderingWidget::RenderingWidget(core::Network& rendering_network, QWidget *parent):
    network{rendering_network},
    QOpenGLWidget(parent),
    vertex_buffer(QOpenGLBuffer::VertexBuffer),
    human_control(rendering_network),

    window_scale{2},
    clear_color(QColor(255,255,255))

{
    renderingWidget = this;
    resize(640, 480);


}



RenderingWidget::~RenderingWidget()
{
}

void RenderingWidget::draw_unit_rect()
{
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void RenderingWidget::draw_lines(std::size_t qty)
{
    glLineWidth(1*window_scale);
    glDrawArrays(GL_LINES, 0, qty);
}



void RenderingWidget::initializeGL()
{
    initializeOpenGLFunctions();

    prepare_rendering_resources();
    human_control.initializeGL();

    prepare_graphic_settings();
}



void RenderingWidget::prepare_rendering_resources()
{

    Arrow::init();
    Rectangle::init();
    Sprite::init();

    vao_link_lines.create();
    vao_link_lines.bind();
    link_lines_buffer.create();
    link_lines_buffer.bind();
    shaders_link_lines.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/selection.vert");
    shaders_link_lines.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/selection.frag");
    shaders_link_lines.enableAttributeArray(Sprite::PROGRAM_VERTEX_ATTRIBUTE);
    shaders_link_lines.setAttributeBuffer(Sprite::PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
    shaders_link_lines.bindAttributeLocation("vertex", Sprite::PROGRAM_VERTEX_ATTRIBUTE);
    shaders_link_lines.link();

    textures = {
        new QOpenGLTexture(QImage(resource_path+"sprites/node.png").mirrored()),
        new QOpenGLTexture(QImage(resource_path+"sprites/bend.png").mirrored()),
        new QOpenGLTexture(QImage(resource_path+"sprites/hub.png").mirrored())
    };
}

void RenderingWidget::prepare_graphic_settings()
{
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_ALPHA);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(clear_color.redF(), clear_color.greenF(), clear_color.blueF(), clear_color.alphaF());

}

void RenderingWidget::resizeGL(int width, int height)
{
    window_rect.setWidth(width);
    window_rect.setHeight(height);

    projection_matrix = QMatrix4x4();
    projection_matrix.ortho(
        -window_rect.width()/2,
         window_rect.width(),
        -window_rect.height()/2,
         window_rect.height(), -1.0f, 1.0f);


    GLfloat aspect_ratio = 1.5;
    if (width > height) {
        //
    } else {

    }
}

void RenderingWidget::mousePressEvent(QMouseEvent *event)
{
    human_control.mouse_press(event);
}

void RenderingWidget::mouseMoveEvent(QMouseEvent *event)
{
    human_control.mouse_move(event);
}

void RenderingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    human_control.mouse_release(event);
}

void RenderingWidget::wheelEvent(QWheelEvent *event)
{
    human_control.mouse_wheel(event);
}

void RenderingWidget::keyPressEvent(QKeyEvent *event)
{
    human_control.key_press(event);
}




QMatrix4x4 get_projection_according_to_window(const QRectF& screen_rect)
{
    QMatrix4x4 matrix;
    matrix.ortho(
        0,
        screen_rect.width(),
        screen_rect.height(),
        0, -1.0f, 1.0f);
    return matrix;
}
QMatrix4x4 get_projection_according_to_observer_position(const QRectF& screen_rect)
{
    QMatrix4x4 matrix = get_projection_according_to_window(screen_rect);
    matrix.translate(screen_rect.x(),
                       screen_rect.y(), 0);
    return matrix;
}




void RenderingWidget::paintGL()
{
    test::debug.profiler.start("RenderingWidget::paintGL");
    glClear(GL_COLOR_BUFFER_BIT);


    projection_matrix = get_projection_according_to_window(window_rect);

    human_control.draw();


    projection_matrix = get_projection_according_to_observer_position(window_rect);
    projection_matrix.scale(window_scale);

    for (core::Node node: network) {
        node.draw();
    }
    test::debug.profiler.stop("RenderingWidget::paintGL");
}




}
