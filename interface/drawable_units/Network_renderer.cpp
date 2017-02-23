#include "Network_renderer.h"

#include "core/Network/Network.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"
#include "interface/primitives/Rectangle/Rectangle.h"
#include "interface/primitives/Arrow/Arrow.h"

//test
#include "interface/RenderingWidget.h"

namespace render {




Network_renderer::Network_renderer(core::Network &in_network, View_data &in_view_data,
        Text_drawer &in_text_drawer
        ):
    network{in_network},
    view_data{in_view_data},
    text_drawer{in_text_drawer}
{

}

void Network_renderer::initializeGL()
{
    initializeOpenGLFunctions();

    sprite.init();
    arrow.init();

    drawn_data.vao.create();
    drawn_data.vao.bind();
    drawn_data.buffer.create();
    drawn_data.buffer.bind();
    drawn_data.shaders.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/lines.vert");
    drawn_data.shaders.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/lines.frag");
    drawn_data.shaders.enableAttributeArray(Sprite::PROGRAM_VERTEX_ATTRIBUTE);
    drawn_data.shaders.setAttributeBuffer(Sprite::PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 2, 6 * sizeof(GLfloat));
    drawn_data.shaders.bindAttributeLocation("vertex", Sprite::PROGRAM_VERTEX_ATTRIBUTE);
    drawn_data.shaders.enableAttributeArray(1);
    drawn_data.shaders.setAttributeBuffer(1, GL_FLOAT, 2 * sizeof(GLfloat), 4, 6 * sizeof(GLfloat));
    drawn_data.shaders.bindAttributeLocation("color",1);
    drawn_data.shaders.link();
    

}


void Network_renderer::draw()
{
    draw_unit_sprites();
    draw_link_lines();
    draw_arrows();
    draw_text_in_units();
}

void Network_renderer::draw_text_in_node(core::Node node) const
{
    Matrix matrix{view_data.projection_matrix};
    matrix.translate(node.position()+Point(0,node.radius+5));
    text_drawer.set_matrix(matrix);
    text_drawer.write(QString("%1").arg(node.name()), 15, Color(.2,.1,0,0));
}
void Network_renderer::draw_text_in_bend(core::Bend bend) const
{
    Matrix matrix{view_data.projection_matrix};
    
    if (bend.interval().start != bend.interval().end) {
        matrix.translate(bend.position()+Point(-bend.radius*3,-bend.radius*3));
        text_drawer.set_matrix(matrix);
        text_drawer.write(QString("%1 %2").arg(bend.interval().start).arg(bend.interval().end), 15, Color(.6,.4,.1,0));
    } else {
        matrix.translate(bend.position()+Point(0,-bend.radius*3));
        text_drawer.set_matrix(matrix);
        text_drawer.write(QString::number(bend.interval().start), 15, Color(.6,.4,.1,0));
    }
    
    matrix = view_data.projection_matrix;
    matrix.translate(bend.position()+Point(0,bend.radius*3));
    text_drawer.set_matrix(matrix);
    text_drawer.write(QString("%1").arg(bend.get_master_node().name()), 15, Color(.2,.1,0,0));
}
void Network_renderer::draw_text_in_hub(core::Hub hub) const
{
    Matrix matrix{view_data.projection_matrix};

    matrix = view_data.projection_matrix;
    matrix.translate(hub.position()+Point(0,hub.radius*3));
    text_drawer.set_matrix(matrix);
    text_drawer.write(QString("%1").arg(hub.name()), 15, Color(.2,.1,0,0));
}

void Network_renderer::draw_text_in_units()const
{
    for (core::Node node: network) {
        draw_text_in_node(node);
        for (core::Bend bend: node.bends()) {
            draw_text_in_bend(bend);
        }
        for (core::Hub hub: node) {
            draw_text_in_hub(hub);
        }
    }
}

void Network_renderer::draw_unit_sprites()
{
    Rectangle::vao_rect.bind();
    Sprite::shaders.bind();
    render::Node::get_texture()->bind();
    for (core::Node node: network) {
        node.prepare_draw_data(drawn_data.vertices);
        node.prepare_shader_for_drawing(view_data.projection_matrix, sprite.shaders);
        sprite.draw();
        
    }
    render::Bend::get_texture()->bind();
    for (core::Node node: network) {
        for (core::Bend bend: node.bends()) {
            bend.prepare_draw_data(drawn_data);
            bend.prepare_shader_for_drawing(view_data.projection_matrix, sprite.shaders);
            sprite.draw();
        }
    }
    render::Hub::get_texture()->bind();
    for (core::Node node: network) {
        for (core::Hub hub: node) {
            hub.prepare_draw_data(drawn_data.vertices);
            hub.prepare_shader_for_drawing(view_data.projection_matrix, sprite.shaders);
            sprite.draw();
        }
    }
    
}

void Network_renderer::draw_link_lines()
{
    drawn_data.vao.bind();
    drawn_data.buffer.bind();
    drawn_data.buffer.allocate(
                drawn_data.vertices.data(), drawn_data.vertices.size() * sizeof(Vertex_colored));
    drawn_data.shaders.bind();

    drawn_data.shaders.setUniformValue("matrix", view_data.projection_matrix);

    glLineWidth(1*view_data.window_scale);
    glDrawArrays(GL_LINES, 0, drawn_data.vertices.size());
    drawn_data.vertices.clear();

}

void Network_renderer::draw_arrows()
{
    Arrow::vertex_array.bind();
    Arrow::vertex_buffer.bind();
    Arrow::shaders.bind();

    for (const Arrow_vector& arrow_vector: drawn_data.arrow_vectors) {
        QMatrix4x4 matrix = view_data.projection_matrix;
        matrix.translate(QVector3D(arrow_vector.position));
        matrix.rotate(arrow_vector.direction, 0,0,1);
        Arrow::shaders.setUniformValue("matrix", matrix);
        Arrow::shaders.setUniformValue("color", Color::fromRgbF(0,0,0,0.5));
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    drawn_data.arrow_vectors.clear();

}



}
