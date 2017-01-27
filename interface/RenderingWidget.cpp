#include "RenderingWidget.h"

#include <QDebug>
#include <QString>

#include "core/Network/Network.h"


namespace render {

const QString RenderingWidget::resource_path="D:/program/cognitus/interface/";
//const QString RenderingWidget::resource_path="/home/v/proger/cognitus/interface/";
//const QString RenderingWidget::resource_path="C:/proger/cognitus/interface/";

RenderingWidget* renderingWidget;


RenderingWidget::RenderingWidget(core::Network& rendering_network, QWidget *parent):
    network(rendering_network),
    QOpenGLWidget(parent),
    vertex_buffer(QOpenGLBuffer::VertexBuffer),
    selection_vertices(QOpenGLBuffer::VertexBuffer),

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
    prepare_graphic_settings();

    update_selection_rect();
}



void RenderingWidget::prepare_rendering_resources()
{
    shader_program.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/sprite.vert");
    shader_program.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/sprite.frag");

    shader_selection.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/selection.vert");
    shader_selection.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/selection.frag");



    static const GLfloat sprite_coordinates[4][2] = {
         { -1, -1}, { +1, -1}, { +1, +1}, { -1, +1 }
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




    QVector<Vertex> vertices_selection;
    vertices_selection.push_back(Vertex{ -30,-30,0,0});
        vertices_selection.push_back(Vertex{ 30,-30,1,0});
        vertices_selection.push_back(Vertex{ 30, 30, 1,1});
        vertices_selection.push_back(Vertex{ -30,30,0,1});
    vao_selection_rect.create();
    vao_selection_rect.bind();
    selection_vertices.create();
    selection_vertices.bind();
    selection_vertices.allocate(vertices_selection.constData(), vertices_selection.count() * sizeof(Vertex));



    shader_selection.enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    shader_selection.setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));




    textures = {
        new QOpenGLTexture(QImage(resource_path+"sprites/node.png")),
        new QOpenGLTexture(QImage(resource_path+"sprites/bend.png")),
        new QOpenGLTexture(QImage(resource_path+"sprites/hub.png"))
    };




    shader_program.bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    shader_program.bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    shader_selection.bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    shader_program.link();
    shader_selection.link();
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

    QVector2D position(0,0);
    QVector2D offset(50,0);
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
        -screen_rect.width()/2,
         screen_rect.width(),
        -screen_rect.height()/2,
         screen_rect.height(), -1.0f, 1.0f);
    return matrix;
}
QMatrix4x4 get_projection_according_to_observer_position(const QRectF& screen_rect)
{
    QMatrix4x4 matrix = get_projection_according_to_window(screen_rect);
    matrix.translate(screen_rect.x()*1.5,
                       -screen_rect.y()*1.5, 0);
    return matrix;
}


void RenderingWidget::update_selection_rect()
{
    QVector<Vertex> vertices_selection;
    /*vertices_selection.push_back(Vertex{ -160,16,0,0});
        vertices_selection.push_back(Vertex{ human_control.mouse_state.position.x()/500,16,0,0});
        vertices_selection.push_back(Vertex{ human_control.mouse_state.position.x()/500, -human_control.mouse_state.position.y()/500, 0,0});
        vertices_selection.push_back(Vertex{ -160,human_control.mouse_state.position.y()/500,0,0});
*/
    vertices_selection.push_back(Vertex{ -5,5,0});
        vertices_selection.push_back(Vertex{ 5,5,0,0});
        vertices_selection.push_back(Vertex{ 5, -5, 0,0});
        vertices_selection.push_back(Vertex{ -5,5,0,0});


    //vao_selection_rect.bind();
    //selection_vertices.bind();
    //selection_vertices.allocate(vertices_selection.constData(), vertices_selection.count() * sizeof(Vertex));


}

void RenderingWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
//



    //QMatrix4x4 selection_matrix = get_projection_according_to_window(window_rect);
    //shader_selection.setUniformValue("matrix", selection_matrix);

    //draw_unit_rect();

    projection_matrix = get_projection_according_to_window(window_rect);

    shader_selection.bind();
    vao_selection_rect.bind();
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
