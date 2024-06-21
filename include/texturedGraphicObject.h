#ifndef GRAPHIC_OBJECT_CLASS_H
#define GRAPHIC_OBJECT_CLASS_H

#include"vaoClass.h"
#include"vboClass.h"
#include"eboClass.h"
#include"texture.h"
#include"shaderClass.h"
#include <string> 

class texturedGraphicObject{
public:

    VAO_Object VAO; //Vertex Array Object (To Store VBO and EBO info)
    VBO_Object VBO; //Vertex Buffer Object
    EBO_Object EBO; //Index/Element Buffer Object
    int indexArraySize; //number of elements in the index buffer
    Shader *compiledTextureShaderProgram;

    texturedGraphicObject(
        GLfloat *vertexArray, 
        GLsizeiptr vertexArraySize,
        GLuint *indexArray, 
        GLsizeiptr indexArraySize,
        Shader *compiledTextureShaderProgram
        ){ 
        
        //setting class attributesc++ change value of class attribute from inside function
        texturedGraphicObject::indexArraySize = indexArraySize;
        texturedGraphicObject::compiledTextureShaderProgram = compiledTextureShaderProgram;

        //#Adding data to VBO and EBO
        VBO.addData(vertexArray, vertexArraySize);
        EBO.addData(indexArray, indexArraySize);

        //#Configure VAO to link with the date inside the VBO and EBO
        VAO.Bind();
        VBO.Bind();
        EBO.Bind();
        

        /* Position attribute */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);// enable vertex attribute 0 for currently defined VAO        

        /* texture attribute */
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1); // enable vertex attribute 2 for currently defined VAO
    

        // return back to noral state
        VAO.Unbind();
        VBO.Unbind();
        EBO.Unbind(); //don't unbind the EBO before unbinding your VAO
        
    }

    

    void drawObject(Texture *texture_object_pointer, GLint texture_unit= 0){

        Shader shader_to_use= *compiledTextureShaderProgram;
        Texture texture_to_use= *texture_object_pointer;

        //changing shader to the one requred for this object if needed
        GLint currentShaderProgramID;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShaderProgramID);
        if(currentShaderProgramID != shader_to_use.shaderProgramID){
            shader_to_use.Activate();
        }

        texture_to_use.Bind(texture_unit);
        texture_to_use.setTextureUnitUniformValue(shader_to_use, "tex0", 0);
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

    void deleteObject(){
        VAO.Delete();
        VBO.Delete();
        EBO.Delete();
    }

};

#endif