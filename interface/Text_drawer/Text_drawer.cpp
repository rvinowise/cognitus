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
    
    static const Point sprite_coordinates[4] = {
          { -1, +1 }, { +1, +1}, { +1, -1},{ -1, -1}
    };

    static Point char_rect{32,32};
    static size_t horizontal_qty{image.rect().width()/char_rect.x()};
    static size_t vertical_qty{image.rect().height()/char_rect.y()};
    
    QPoint char_place_in_table{0,0};
    for (char symbol: char_sequence) {
        QOpenGLBuffer* char_buffer = new QOpenGLBuffer();
        symbol_vertices[symbol] = char_buffer;


        static Point texture_offset{char_rect.x()/image.rect().width(),
                                   char_rect.y()/image.rect().height()};
        Point texture_bottom_left{
            char_place_in_table.x()*texture_offset.x(),
            (vertical_qty-char_place_in_table.y()-1)*texture_offset.y()
        };
        Point texture_upper_right{texture_bottom_left+texture_offset};


        std::vector<Vertex> vertices;
        /*vertices.push_back(Vertex{
                               sprite_coordinates[0]*50,
                               texture_bottom_left.x(),
                               texture_bottom_left.y()
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[1]*50,
                               texture_bottom_left.x()+texture_offset.x(),
                               texture_bottom_left.y()
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[2]*50,
                               texture_bottom_left.x()+texture_offset.x(),
                               texture_bottom_left.y()+texture_offset.y(),
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[3]*50,
                               texture_bottom_left.x(),
                               texture_bottom_left.y()+texture_offset.y()
                           });*/
        vertices.push_back(Vertex{
                               sprite_coordinates[0]*50,
                               0,
                               0
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[1]*50,
                               1,
                               0
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[2]*50,
                               1,
                               1,
                           });
        vertices.push_back(Vertex{
                               sprite_coordinates[3]*50,
                               0,
                               1
                           });
        char_buffer->allocate(vertices.data(), vertices.size()*sizeof(Vertex));


        ++char_place_in_table.rx();
        if (char_place_in_table.x() >= horizontal_qty) {
            ++char_place_in_table.ry();
            char_place_in_table.setX(0);
        }
    }
    
}


void Text_drawer::write(std::string string)
{
    //
    symbol_vertices['D']->bind();
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
