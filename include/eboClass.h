#pragma once
#ifndef EBO_CLASS_H 
#define EBO_CLASS_H

#include <GL/glew.h>

class EBO_Object{

public:

    // Reference ID of the Element Buffer Object
	GLuint EBO_ID;
    
	// Constructor that generates a Element Buffer Object and links it to indices
	EBO_Object();

	void addData(GLuint* indices, GLsizeiptr size);

	// Binds the VBO
	void Bind();

	// Unbinds the VBO
	void Unbind();

	// Deletes the VBO
	void Delete();


};

#endif