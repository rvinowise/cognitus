#include "Arrow.h"

#include "interface/primitives/Vertex/Vertex.h"

#include "interface/RenderingWidget.h"
namespace render {

QOpenGLVertexArrayObject Arrow::vertex_array{};
QOpenGLBuffer Arrow::vertex_buffer{};
QOpenGLShaderProgram Arrow::shaders{};

Arrow::Arrow()
{

}


void Arrow::init()
{
    initializeOpenGLFunctions();
    static const GLfloat sprite_coordinates[3][2] = {
          { +0.2, 1 }, { 0, 0.2}, { -0.2, 1}
    };


    QVector<Vertex_point> vertices;
    for (int j = 0; j < 3; ++j) {
        vertices.push_back(Vertex_point{
                               sprite_etalon_radius * sprite_coordinates[j][0],
                               sprite_etalon_radius * sprite_coordinates[j][1]
                           });
    }
    vertex_array.create();
    vertex_array.bind();
    vertex_buffer.create();
    vertex_buffer.bind();
    vertex_buffer.allocate(vertices.constData(), vertices.count() * sizeof(Vertex));


    shaders.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/arrow.vert");
    shaders.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/arrow.frag");

    static const std::size_t attrib_vertex = 0;
    shaders.enableAttributeArray(attrib_vertex);
    shaders.setAttributeBuffer(attrib_vertex, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));

    shaders.bindAttributeLocation("vertex", attrib_vertex );
    shaders.link();
}

void Arrow::draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


}
