#include "Network_renderer.h"

#include "core/Network/Network.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"
#include "interface/primitives/Rectangle/Rectangle.h"
#include "interface/primitives/Arrow/Arrow.h"

//test
#include "interface/RenderingWidget.h"

namespace render {




Network_renderer::Network_renderer(
        core::Network &in_network,
        QPaintDevice* in_paint_device
        ):
    network{in_network},
    paint_device{in_paint_device}
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
    
    drawn_data.buffer.release();
    drawn_data.vao.release();
    

}


void Network_renderer::draw(const View_data &view_data)
{
    draw_unit_sprites(view_data);
    draw_link_lines(view_data);
    draw_arrows(view_data);
    //draw_text_in_units(view_data);
}

void Network_renderer::draw_text_in_units(const View_data &view_data)
{
    static QPainter painter(paint_device);
    painter.drawText(50,50,"LOL");
    for (core::Node node: network) {
        for (core::Bend bend: node.bends()) {
            
        }
    }
}

void Network_renderer::draw_unit_sprites(const View_data &view_data)
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
    
    Rectangle::vao_rect.release();
}

void Network_renderer::draw_link_lines(const View_data &view_data)
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

void Network_renderer::draw_arrows(const View_data &view_data)
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
    
    Arrow::vertex_buffer.release();
    Arrow::vertex_array.release();
}



}
