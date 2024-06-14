#include <vboClass.h>
#include <GL/glew.h>

VBO_Object::VBO_Object(){

    //creating a vbo and storing its ID in the id variable
    glGenBuffers(1, &VBO_ID);

}

void VBO_Object::addData(GLfloat* vertices, GLsizeiptr size){
    //making our VBO active 
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);

    // Add data into the currently active VBO atribute
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    //deactivating it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO_Object::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
}

void VBO_Object::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO_Object::Delete(){
    glDeleteBuffers(1, &VBO_ID);
}

