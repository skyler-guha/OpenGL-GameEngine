#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>
#include"vboClass.h"
#include"eboClass.h"

class VAO_Object
{
public:
	// ID reference for the Vertex Array Object
	GLuint VAO_ID;
	// Constructor that generates a VAO ID
	VAO_Object();

	// Binds the VAO
	void Bind();

	// Unbinds the VAO
	void Unbind();

	// Deletes the VAO
	void Delete();
};
#endif