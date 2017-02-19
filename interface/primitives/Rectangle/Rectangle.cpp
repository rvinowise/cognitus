#include "Rectangle.h"

#include "interface/primitives/Vertex/Vertex.h"
#include "interface/RenderingWidget.h"


namespace render {

QOpenGLVertexArrayObject Rectangle::vao_rect{};
QOpenGLBuffer Rectangle::vertex_buffer{};


Rectangle::Rectangle()
{

}

void Rectangle::init()
{
    static const Point sprite_coordinates[4] = {
          { -1, +1 }, { +1, +1}, { +1, -1},{ -1, -1}
    };


    QVector<Vertex> vertices;
    for (int j = 0; j < 4; ++j) {
        vertices.push_back(Vertex{
                               sprite_etalon_radius * sprite_coordinates[j],
                               j == 2 || j == 1,
                               j == 2 || j == 3
                           });
    }
    vao_rect.create();
    vao_rect.bind();
    vertex_buffer.create();
    vertex_buffer.bind();
    vertex_buffer.allocate(vertices.constData(), vertices.count() * sizeof(Vertex));
}

QOpenGLShaderProgram Sprite::shaders{};
std::vector<QOpenGLTexture*> Sprite::textures;
//float Sprite::etalon_radius = 10;

Sprite::Sprite()
{

}

void Sprite::init()
{
    Rectangle::init();
    initializeOpenGLFunctions();

    shaders.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/sprite.vert");
    shaders.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/sprite.frag");

    shaders.enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    shaders.enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    shaders.setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));
    shaders.setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 2 * sizeof(GLfloat), 2, 4 * sizeof(GLfloat));

    shaders.bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    shaders.bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    shaders.link();
    shaders.setUniformValue("texture", 0);

    textures = {
        new QOpenGLTexture(QImage(resource_path+"sprites/node.png").mirrored()),
        new QOpenGLTexture(QImage(resource_path+"sprites/bend.png").mirrored()),
        new QOpenGLTexture(QImage(resource_path+"sprites/hub.png").mirrored())
    };
}

void Sprite::draw()
{
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


}
