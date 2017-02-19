#include "Text_drawer.h"

#include "QFile"
#include <boost/format.hpp>

#include "core/test/Debug_inspector.h"
#include "interface/primitives/Rectangle/Rectangle.h"


namespace render {


Text_drawer::Text_drawer()
{
    
}

void Text_drawer::initializeGL()
{
    initializeOpenGLFunctions();
}



void Text_drawer::load_font(QString file_name)
{
    QImage image(resource_path+"sprites/"+file_name);
    symbol_table = new QOpenGLTexture(image.mirrored());        
    
    static Point char_rect{32,32};
    static size_t horizontal_qty{image.rect().width()/char_rect.x()};
    static size_t vertical_qty{image.rect().height()/char_rect.y()};
    
    for (char symbol: char_sequence) {
        QOpenGLBuffer* char_buffer = new QOpenGLBuffer();
        symbol_vertices[symbol] = char_buffer;
        char_buffer->allocate(vertices.data(), vertices.size()*sizeof(Vertex));
        vertices.clear();
    }
    
    static const GLfloat sprite_coordinates[4][2] = {
          { -1, +1 }, { +1, +1}, { +1, -1},{ -1, -1}
    };
    
    
    image.rect();
    //Rect symbol_rect_pixels();
    

    std::vector<Vertex> vertices;

    vertices.push_back(Vertex{
                           sprite_coordinates[0][0],
                           sprite_coordinates[0][1],
                           0.5,
                           0.7
                       });

    
    
    
    symbol_vertices['a'] = new QOpenGLBuffer();
    symbol_vertices['a']->allocate(vertices.data(), vertices.size()*sizeof(Vertex));
    vertices.clear();
    for (int j = 0; j < 4; ++j) {
        vertices.push_back(Vertex{
                               sprite_etalon_radius * sprite_coordinates[j][0],
                               sprite_etalon_radius * sprite_coordinates[j][1],
                               0.5,
                               0.7
                           });
    }
    symbol_vertices['b'] = new QOpenGLBuffer();
    symbol_vertices['b']->allocate(vertices.data(), vertices.size()*sizeof(Vertex));
}


void Text_drawer::write(std::string string)
{
    symbol_vertices['a']->bind();
    //Rectangle::vao_rect.bind();
    Sprite::shaders.bind();
    symbol_table->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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
    /*char_sequence.resize(symbol_qty);
    for (size_t i_char = 0; i_char < symbol_qty; ++i_char) {
        char_sequence[i_char] =
    }*/
    
    file.close();
}



}
