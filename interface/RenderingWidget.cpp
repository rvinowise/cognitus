#include "RenderingWidget.h"

#include <QDebug>
#include <QString>

#include "core/Network/Network.h"
#include "core/Network/Node/Iterator/Iterator_node_BFS.h"
#include "interface/drawable_units/draw_Node.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"
#include "core/Network/Node/Iterator/Iterator_node_BFS.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"
//#include "interface/primitives/Vertex/Vertex.h"
#include "algorithms.h"
#include "core/test/Debug_inspector.h"



namespace render {

QPainter p;

RenderingWidget::RenderingWidget(core::Network& rendering_network, QWidget *parent):
    network{rendering_network},
    QOpenGLWidget(parent),
    human_control(rendering_network, disposer, view_data),
    network_renderer(rendering_network, this),
    text_drawer(view_data),
    clear_color(QColor(255,255,255))

{
    resize(640, 480);


}



RenderingWidget::~RenderingWidget()
{
}


void RenderingWidget::initializeGL()
{
    initializeOpenGLFunctions();
    
    human_control.initializeGL();
    network_renderer.initializeGL();
    text_drawer.initializeGL();
    prepare_graphic_settings();
    
    text_drawer.load_char_sequence_in_symbol_table("char_sequence.txt");
    text_drawer.load_font("consolas.bmp");
    
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
    view_data.window_rect.setWidth(width);
    view_data.window_rect.setHeight(height);

    view_data.projection_matrix = QMatrix4x4();
    view_data.projection_matrix.ortho(
        -view_data.window_rect.width()/2,
         view_data.window_rect.width(),
        -view_data.window_rect.height()/2,
         view_data.window_rect.height(), -1.0f, 1.0f);


    GLfloat aspect_ratio = 1.5;
    if (width > height) {
        //
    } else {

    }
}

void RenderingWidget::mousePressEvent(QMouseEvent *event)
{
    human_control.mouse_press(event);
    update_if_need();
}

void RenderingWidget::mouseMoveEvent(QMouseEvent *event)
{
    human_control.mouse_move(event);
    update_if_need();
}

void RenderingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    human_control.mouse_release(event);
    update_if_need();
}

void RenderingWidget::wheelEvent(QWheelEvent *event)
{
    human_control.mouse_wheel(event);
    update_if_need();
}

void RenderingWidget::keyPressEvent(QKeyEvent *event)
{
    human_control.key_press(event);
    update_if_need();
}

void RenderingWidget::update_if_need()
{
    if (human_control.world_changed) {
        update();
    }
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
QMatrix4x4 get_projection_according_to_observer_position(const QRectF& screen_rect, float window_scale)
{
    QMatrix4x4 matrix = get_projection_according_to_window(screen_rect);
    matrix.scale(window_scale);
    matrix.translate(-screen_rect.x(),
                     -screen_rect.y(), 0);
    
    return matrix;
}




void RenderingWidget::paintGL()
{
    test::debug.profiler.start("RenderingWidget::paintGL");

    glClear(GL_COLOR_BUFFER_BIT);

    view_data.projection_matrix = get_projection_according_to_observer_position(view_data.window_rect, view_data.window_scale);
    network_renderer.draw(view_data);

    ////view_data.projection_matrix = get_projection_according_to_window(view_data.window_rect);
    human_control.draw();
    
    view_data.projection_matrix = get_projection_according_to_observer_position(view_data.window_rect, view_data.window_scale);
    view_data.projection_matrix.translate(400,200,0);
    text_drawer.write("verte lapides in frumenta 123 456 789 0 lol",21,Color(0.1,0.9,0.9));
    
    test::debug.profiler.stop("RenderingWidget::paintGL");
}





}
