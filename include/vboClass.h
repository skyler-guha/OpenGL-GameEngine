#pragma once
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>

class VBO_Object{
	
public:
	// Reference ID of the Vertex Buffer Object
	GLuint VBO_ID;
    
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO_Object();

	void addData(GLfloat* vertices, GLsizeiptr size);

	// Binds the VBO
	void Bind();

	// Unbinds the VBO
	void Unbind();

	// Deletes the VBO
	void Delete();
};

#endif