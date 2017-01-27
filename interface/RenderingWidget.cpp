#include "RenderingWidget.h"

#include <QDebug>
#include <QString>

#include "core/Network/Network.h"


namespace render {

//const QString RenderingWidget::resource_path="D:/program/cognitus/interface/";
//const QString RenderingWidget::resource_path="/home/v/proger/cognitus/interface/";
const QString RenderingWidget::resource_path="C:/proger/cognitus/interface/";

RenderingWidget* renderingWidget;


RenderingWidget::RenderingWidget(core::Network& rendering_network, QWidget *parent):
    network(rendering_network),
    QOpenGLWidget(parent),
    vertex_buffer(QOpenGLBuffer::VertexBuffer),

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
void RenderingWidget::draw_selection_rect()
{
    //glBlendColor(0.0f,1.0f,0.0f,0.5f);
    glLineWidth(3);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}



void RenderingWidget::initializeGL()
{
    initializeOpenGLFunctions();

    prepare_rendering_resources();
    human_control.initializeGL();

    prepare_graphic_settings();

    update_selection_rect();
}



void RenderingWidget::prepare_rendering_resources()
{
    shader_program.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/sprite.vert");
    shader_program.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/sprite.frag");


    static const GLfloat sprite_coordinates[4][2] = {
          { -1, +1 }, { +1, +1}, { +1, -1},{ -1, -1}
    };
    static GLfloat sprite_scale = 10;

    QVector<Vertex> vertices;
    for (int j = 0; j < 4; ++j) {
        vertices.push_back(Vertex{
                               sprite_scale * sprite_coordinates[j][0],
                               sprite_scale * sprite_coordinates[j][1],
                               j == 2 || j == 1,
                               j == 2 || j == 3
                           });
    }
    vao_sprite_rect.create();
    vao_sprite_rect.bind();
    vertex_buffer.create();
    vertex_buffer.bind();
    vertex_buffer.allocate(vertices.constData(), vertices.count() * sizeof(Vertex));

    shader_program.enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    shader_program.enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    shader_program.setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));
    shader_program.setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 2 * sizeof(GLfloat), 2, 4 * sizeof(GLfloat));


    textures = {
        new QOpenGLTexture(QImage(resource_path+"sprites/node.png").mirrored()),
        new QOpenGLTexture(QImage(resource_path+"sprites/bend.png").mirrored()),
        new QOpenGLTexture(QImage(resource_path+"sprites/hub.png").mirrored())
    };


    shader_program.bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    shader_program.bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    shader_program.link();
    shader_program.setUniformValue("texture", 0);


    initialize_units();
}

void RenderingWidget::prepare_graphic_settings()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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

void RenderingWidget::initialize_units()
{
    int test = network.input.getNodesQty();

    Point position(100,50);
    Point offset(50,0);
    for (auto input_node: network.input) {
        units.push_back(Drawable_unit());
        units.back().texture = textures[0];
        units.back().position = position;
        position += offset;
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
QMatrix4x4 get_projection_according_to_observer_position(const QRectF& screen_rect)
{
    QMatrix4x4 matrix = get_projection_according_to_window(screen_rect);
    matrix.translate(screen_rect.x(),
                       screen_rect.y(), 0);
    return matrix;
}


void RenderingWidget::update_selection_rect()
{

}

void RenderingWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);



    //QMatrix4x4 selection_matrix = get_projection_according_to_window(window_rect);
    //shader_selection.setUniformValue("matrix", selection_matrix);

    //draw_unit_rect();

    projection_matrix = get_projection_according_to_window(window_rect);

    human_control.draw();


    projection_matrix = get_projection_according_to_observer_position(window_rect);

    shader_program.bind();
    vao_sprite_rect.bind();

    int i=0;
    for (Drawable_unit& drawable: units) { 
        drawable.draw();

        ++i;
    }
}




}
