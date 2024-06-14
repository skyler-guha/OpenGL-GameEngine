#include <eboClass.h>
#include <GL/glew.h>

EBO_Object::EBO_Object(){

    //creating a ebo and storing its ID in the id variable
    glGenBuffers(1, &EBO_ID);
}


void EBO_Object::addData(GLuint* indices, GLsizeiptr size){
    //making our EBO active 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);

    // Add data into the currently active EBO atribute
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    //deactivting it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO_Object::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
}

void EBO_Object::Unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO_Object::Delete(){
    glDeleteBuffers(1, &EBO_ID);
}

