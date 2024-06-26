#include "shaderClass.h"

#include <iostream>
#include <fstream>
#include <GL/glew.h>


std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    //check variable
    int shader_compile_sucess;

	

	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexShaderPath);
	
	std::string fragmentCode = get_file_contents(fragmentShaderPath);

	

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
    //check if the vertex shader compiled correctly
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shader_compile_sucess);
    if (!shader_compile_sucess) {
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }



	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
    //check if the fragment shader compiled correctly
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shader_compile_sucess);
    if (!shader_compile_sucess) {
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }


	// Create Shader Program Object and get its reference
	shaderProgramID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgramID);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(shaderProgramID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(shaderProgramID);
}



