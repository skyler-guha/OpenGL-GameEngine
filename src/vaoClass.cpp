#include"vaoClass.h"
#include"eboClass.h"

// Constructor that generates a VAO ID
VAO_Object::VAO_Object()
{
	glGenVertexArrays(1, &VAO_ID);
}


// Binds the VAO
void VAO_Object::Bind()
{
	glBindVertexArray(VAO_ID);
}

// Unbinds the VAO
void VAO_Object::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO_Object::Delete()
{
	glDeleteVertexArrays(1, &VAO_ID);
}