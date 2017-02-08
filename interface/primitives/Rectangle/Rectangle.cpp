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
    static const GLfloat sprite_coordinates[4][2] = {
          { -1, +1 }, { +1, +1}, { +1, -1},{ -1, -1}
    };


    QVector<Vertex> vertices;
    for (int j = 0; j < 4; ++j) {
        vertices.push_back(Vertex{
                               sprite_etalon_radius * sprite_coordinates[j][0],
                               sprite_etalon_radius * sprite_coordinates[j][1],
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
void Sprite::init()
{
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
}

void Sprite::draw()
{
    renderingWidget->glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


}
