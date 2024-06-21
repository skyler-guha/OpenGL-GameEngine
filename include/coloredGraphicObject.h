#ifndef GRAPHIC_OBJECT_CLASS_H
#define GRAPHIC_OBJECT_CLASS_H

#include"vaoClass.h"
#include"vboClass.h"
#include"eboClass.h"
#include <string> 
#include <iostream>



class coloredGraphicObject{
public:

    VAO_Object VAO; //Vertex Array Object (To Store VBO and EBO info)
    VBO_Object VBO; //Vertex Buffer Object
    EBO_Object EBO; //Index/Element Buffer Object
    int indexArraySize; //number of elements in the index buffer
    GLint compiledColorShaderProgramID;

    coloredGraphicObject::coloredGraphicObject(
        GLfloat* vertexArray, 
        GLsizeiptr vertexArraySize,
        GLuint* indexArray, 
        GLsizeiptr indexArraySize,
        GLint compiledColorShaderProgramID){ 
        
        //setting class attributes
        coloredGraphicObject::indexArraySize = indexArraySize;
        coloredGraphicObject::compiledColorShaderProgramID = compiledColorShaderProgramID;

        //#Adding data to VBO and EBO
        VBO.addData(vertexArray, vertexArraySize);
        EBO.addData(indexArray, indexArraySize);

        //#Configure VAO to link with the date inside the VBO and EBO
        VAO.Bind();
        VBO.Bind();
        EBO.Bind();
        

        /* Position attribute */
        glVertexAttribPointer(
        0,                      // attribute 0. Must match the layout in the shader.
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

    void coloredGraphicObject::drawObject(){

        //changing shader to the one requred for this object if needed
        GLint currentShaderProgramID;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShaderProgramID);
        if(currentShaderProgramID != compiledColorShaderProgramID){
            glUseProgram(compiledColorShaderProgramID);
        }

        VAO.Bind();
        
        //draw our tringle using elements
        glDrawElements(
            GL_TRIANGLES,                           //premetive
            indexArraySize,                          //count of indices
            GL_UNSIGNED_INT,                        // datatype of our values
            0                                       //index of our indices
        );

        VAO.Unbind();
    }

    void coloredGraphicObject::deleteObject(){
        VAO.Delete();
        VBO.Delete();
        EBO.Delete();
    }

};

#endif