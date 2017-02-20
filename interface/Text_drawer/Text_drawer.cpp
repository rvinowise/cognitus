#include "Text_drawer.h"

#include "QFile"
#include <boost/format.hpp>

#include "core/test/Debug_inspector.h"
#include "interface/primitives/Rectangle/Rectangle.h"


namespace render {


void Letter::create_and_prepare_to_fill()
{
    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    vertex_buffer = new QOpenGLBuffer();
    vertex_buffer->create();
    vertex_buffer->bind();
}




Text_drawer::Text_drawer(View_data &in_view_data):
    view_data{in_view_data}
{
    
}

void Text_drawer::initializeGL()
{
    initializeOpenGLFunctions();
    
    shaders.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/text.vert");
    shaders.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/text.frag");
    
    shaders.bindAttributeLocation("vertex", 0);
    shaders.bindAttributeLocation("tex_coord", 1);
    shaders.link();
    //shaders.setUniformValue("matrix", 0);
    shaders.setUniformValue("texture", 1);
    shaders.setUniformValue("color", 2);
}



void Text_drawer::load_font(QString file_name)
{
    QImage image(resource_path+"sprites/"+file_name);
    symbol_table = new QOpenGLTexture(image.mirrored());        
    
    static Point char_rect{12,21};
    font_size = char_rect.y();
    static const Point sprite_coordinates[4] = {
          { 0, char_rect.y() }, {char_rect}, { char_rect.x(), 0},{ 0, 0}
    };

    static size_t horizontal_qty{image.rect().width()/char_rect.x()};
    static size_t vertical_qty{image.rect().height()/char_rect.y()};
    static Point texture_offset{char_rect.x()/image.rect().width(),
                               char_rect.y()/image.rect().height()};
    
    QPoint char_place_in_table{0,0};
    for (char symbol: char_sequence) {
        letters[symbol] = Letter();
        Letter& letter = letters[symbol];
        letter.width=char_rect.x();
        letter.create_and_prepare_to_fill();


        
        Point texture_bottom_left{
            char_place_in_table.x()*texture_offset.x(),
            1-((char_place_in_table.y()+1)*texture_offset.y())
        };
        //Point texture_upper_right{texture_bottom_left+texture_offset};


        std::vector<Vertex> vertices;
        vertices.push_back(Vertex{
                               sprite_coordinates[0],
                               texture_bottom_left.x(),
                               texture_bottom_left.y()
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[1],
                               texture_bottom_left.x()+texture_offset.x(),
                               texture_bottom_left.y()
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[2],
                               texture_bottom_left.x()+texture_offset.x(),
                               texture_bottom_left.y()+texture_offset.y(),
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[3],
                               texture_bottom_left.x(),
                               texture_bottom_left.y()+texture_offset.y()
                           });

        letter.vertex_buffer->allocate(vertices.data(), vertices.size()*sizeof(Vertex));

        
        shaders.enableAttributeArray(0);
        shaders.enableAttributeArray(1);
        shaders.setAttributeBuffer(0, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));
        shaders.setAttributeBuffer(1, GL_FLOAT, 2 * sizeof(GLfloat), 2, 4 * sizeof(GLfloat));
        

        
        
        ++char_place_in_table.rx();
        if (char_place_in_table.x() >= horizontal_qty) {
            ++char_place_in_table.ry();
            char_place_in_table.setX(0);
        }
    }
    
}

void Text_drawer::write(std::string string, float in_size, Color in_color)
{
    QMatrix4x4 matrix{view_data.projection_matrix};
    
    float nearest_font_size = font_size;
    float scaling = in_size / nearest_font_size;
    matrix.scale(scaling);
    for (char next_char: string) {
        symbol_table->bind();
        shaders.bind();
        Letter& letter = letters[next_char];
        letter.vao->bind();    
        
        shaders.setUniformValue("matrix", matrix);
        shaders.setUniformValue("color", Color(1,0,0,0.5));
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        matrix.translate(QVector3D(letter.get_width(),0,0));
    }
}

void Text_drawer::write(std::string string)
{
    write(string, 1, Color::fromRgbF(0,0,0));
}

void Text_drawer::load_char_sequence_in_symbol_table(QString file_name)
{
    QFile file(resource_path+"sprites/"+file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw_msg("load_char_sequence_in_symbol_table !file.open");
    
    QTextStream in(&file);
    while (!in.atEnd()) {
        char next_char;
        in >> next_char;
        char_sequence.push_back(next_char);
    }
    file.close();
}





}
