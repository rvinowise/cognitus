#pragma once

#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <string>
#include <memory>

#include "interface/Human_control/Human_control.h"
#include "interface/common/constants.h"

#include "interface/primitives/Arrow/Arrow.h"
#include "interface/primitives/Rectangle/Rectangle.h"
#include "interface/drawable_units/Network_renderer.h"
#include "interface/View_data/View_data.h"
#include "interface/Text_drawer/Text_drawer.h"

namespace core {
    class Network;
    class Node;
}

namespace render {


class RenderingWidget: public QOpenGLWidget,
                        protected QOpenGLFunctions
{
    friend class Human_control;
    friend class Sprite;
    friend class Arrow;
public:
    explicit RenderingWidget(core::Network &rendering_network, QWidget *parent = 0);
    //explicit RenderingWidget(RenderingWidget* other = 0);
    ~RenderingWidget();

    View_data view_data;


protected:

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    //void paintEvent(QPaintEvent *event) override;
    
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent*event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent*event) Q_DECL_OVERRIDE;

    void update_if_need();

private:
    void update_units_according_to_network();
    void prepare_rendering_resources();
    void prepare_graphic_settings();
    void print_context_information();

    QColor clear_color;

    Human_control human_control;
    render::Network_renderer network_renderer;
    Units_disposer disposer;
    Text_drawer text_drawer;

    core::Network& network;

};



}
