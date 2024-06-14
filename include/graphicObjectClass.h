#ifndef GRAPHIC_OBJECT_CLASS_H
#define GRAPHIC_OBJECT_CLASS_H

#include"vaoClass.h"
#include"vboClass.h"
#include"eboClass.h"

class graphicObject{
public:

    VAO_Object VAO; //Vertex Array Object (To Store VBO and EBO info)
    VBO_Object VBO; //Vertex Buffer Object
    EBO_Object EBO; //Index/Element Buffer Object
    int indices_count ;
    

    //constructor
    graphicObject(GLfloat* vertexArray, GLsizeiptr vertexArraySize,
                  GLuint* indexArray, GLsizeiptr indexArraySize);

    void drawObject();

    void deleteObject();

};

#endif