#pragma once

#include <unordered_map>

#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

namespace render {

class Text_drawer: protected QOpenGLFunctions
{
public:
    Text_drawer();
    void initializeGL();
    
    void load_font(QString in_path);
    void load_char_sequence_in_symbol_table(QString file_name);
    
    void write(std::string in_text);
    
private:
    
    
    QOpenGLTexture* symbol_table;
    std::unordered_map<char, QOpenGLBuffer*> symbol_vertices;
    std::vector<char> char_sequence;
};



}
