#include "RenderingWidget.h"

#include <QDebug>
#include <QString>

#include "core/Network/Network.h"


namespace render {

//const QString RenderingWidget::resource_path="D:/program/cognitus/interface/";
const QString RenderingWidget::resource_path="/home/v/proger/cognitus/interface/";
RenderingWidget* renderingWidget;


RenderingWidget::RenderingWidget(core::Network& rendering_network, QWidget *parent):
    network(rendering_network),
    QOpenGLWidget(parent),

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




void RenderingWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //print_context_information();

    prepare_rendering_resources();
    prepare_graphic_settings();
}

struct Vertex
{
    GLfloat position[2];
    GLfloat texture_coordinates[2];
};

void RenderingWidget::prepare_rendering_resources()
{
    static const GLfloat sprite_coordinates[4][2] = {
         { -1, -1}, { +1, -1}, { +1, +1}, { -1, +1 }
    };
    static GLfloat sprite_scale = 1;

    QVector<Vertex> vertices;
    for (int j = 0; j < 4; ++j) {
        vertices.push_back(Vertex{
                               sprite_scale * sprite_coordinates[j][0],
                               sprite_scale * sprite_coordinates[j][1],
                               j == 2 || j == 1,
                               j == 2 || j == 3
                           });
    }
    vertex_buffer.create();
    vertex_buffer.bind();
    vertex_buffer.allocate(vertices.constData(), vertices.count() * sizeof(Vertex));

    textures = {
        std::make_shared<QOpenGLTexture>(QImage(resource_path+"sprites/node.png")),
        std::make_shared<QOpenGLTexture>(QImage(resource_path+"sprites/bend.png")),
        std::make_shared<QOpenGLTexture>(QImage(resource_path+"sprites/hub.png"))
    };

    shader_program.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/sprite.vert");
    shader_program.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/sprite.frag");

    shader_program.bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    shader_program.bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    shader_program.link();

    shader_program.bind();
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

    shader_program.enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    shader_program.enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    shader_program.setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));
    shader_program.setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 2 * sizeof(GLfloat), 2, 4 * sizeof(GLfloat));

    projection_matrix.ortho(-50.0f, +50.0f, -50.0f, +50.0f, -1.0f, 1.0f);
}

void RenderingWidget::resizeGL(int width, int height)
{

}

void RenderingWidget::mousePressEvent(QMouseEvent *event)
{

}

void RenderingWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void RenderingWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void RenderingWidget::initialize_units()
{
    int test = network.input.getNodesQty();

    QVector2D position(0,0);
    QVector2D offset(2,0);
    for (auto input_node: network.input) {
        drawables.push_back(Drawable_unit());
        drawables.back().texture = textures[0];
        drawables.back().position = position;
        position += offset;
    }
}

void RenderingWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);

    for (Drawable_unit& drawable: drawables) {
        drawable.draw();
    }
}



void RenderingWidget::print_context_information()
{
    QString glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    qDebug() << "OpenGL " << glVersion;

    GLint glParam; glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &glParam);
    qDebug() << glParam;
}


}
