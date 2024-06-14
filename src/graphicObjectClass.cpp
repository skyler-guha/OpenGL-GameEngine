#include"graphicObjectClass.h"


//constructor
graphicObject::graphicObject(GLfloat* vertexArray, GLsizeiptr vertexArraySize,
                GLuint* indexArray, GLsizeiptr indexArraySize){

    
    //#Adding data to VBO and EBO
    VBO.addData(vertexArray, vertexArraySize);
    EBO.addData(indexArray, indexArraySize);
    indices_count = indexArraySize;

    //#Configure VAO to link with the date inside the VBO and EBO

    VAO.Bind();
    VBO.Bind();
    EBO.Bind();
    
    /* Position attribute */
    glVertexAttribPointer(      // tells currently selected VAO what to do with the supplied array data
        0,                      // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // Tells opengl that the attributes are between 0-1
        7 * sizeof(GLfloat),    // stride
        (GLvoid*)0              // array buffer offset
        );

    glEnableVertexAttribArray(0);// enable vertex attribute 0 for currently defined VAO

    /* Color attribute */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // enable vertex attribute 1 for currently defined VAO

    // return back to noral state
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind(); //don't unbind the EBO before unbinding your VAO
}

void graphicObject::drawObject(){

    VAO.Bind();
    
    //draw our tringle using elements
    glDrawElements(
        GL_TRIANGLES,                           //premetive
        indices_count,                          //count of indices
        GL_UNSIGNED_INT,                        // datatype of our values
        0                                       //index of our indices
    );

    VAO.Unbind();
}

void graphicObject::deleteObject(){
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
}

