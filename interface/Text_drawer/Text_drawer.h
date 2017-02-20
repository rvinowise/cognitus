#pragma once

#include <unordered_map>

#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include "interface/View_data/View_data.h"


namespace render {

struct Letter {
    
    
    void create_and_prepare_to_fill();
    float get_width() {return width;}
    
    QOpenGLVertexArrayObject* vao;
    QOpenGLBuffer* vertex_buffer;
    
    float width;
};

class Text_drawer: protected QOpenGLFunctions
{
public:
    Text_drawer(View_data& in_view_data);
    void initializeGL();
    
    void load_font(QString in_path);
    void load_char_sequence_in_symbol_table(QString file_name);
    
    void write(std::string string, float in_size, Color in_color);
    void write(std::string in_text);
    
private:
    View_data& view_data;
    
    QOpenGLTexture* symbol_table;
    std::unordered_map<char,Letter> letters;
    //std::unordered_map<char, QOpenGLBuffer*> symbol_vertices;
    std::vector<char> char_sequence;
    
    QOpenGLShaderProgram shaders;
    
    float font_size;
};



}
