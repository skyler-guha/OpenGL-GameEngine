#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"
#include <SDL2/SDL.h>
//#include <GL/glew.h>

class Camera{
public:
    glm::vec3 Position; //position of the camra in 3D space
    glm::vec3  Orientation = glm::vec3(0.0f, 0.0f, -1.0f); //direction the camera is pointing at.
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); // a vector for telling which direction is up

    // Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.05f;
	float sensitivity = 100.0f;

    // Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position){
        Camera::width= width;
        Camera::height= height;
        Camera::Position= position;
    }

	// Updates and exports the camera matrix (view and projection) to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform){
        
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // Makes camera look in the right direction from the right position
        view = glm::lookAt(Position, Position + Orientation, Up);

        // Adds perspective to the scene
        projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

        // Exports the camera matrix to the Vertex Shader
        glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgramID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
    }
	
    // Handles camera inputs
	void Inputs(SDL_Event event, SDL_Window* sdl_window){//, const Uint8* keyboardState, SDL_Window* sdl_window){

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); //getting keybord state

    // // Handles key inputs
    if (keyboardState[SDL_SCANCODE_W])
    {
        Position += speed * Orientation;
        
    }
    if (keyboardState[SDL_SCANCODE_A])
    {
        Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (keyboardState[SDL_SCANCODE_S])
    {
        Position += speed * -Orientation;
    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        Position += speed * glm::normalize(glm::cross(Orientation, Up));
    }
    if (keyboardState[SDL_SCANCODE_SPACE])
    {
        Position += speed * Up;
    }
    if (keyboardState[SDL_SCANCODE_LSHIFT])
    {
        Position += speed * -Up;
    }

    // if(event.type == SDL_KEYDOWN)
    // {
    //     if (event.key.keysym.sym == SDLK_w)
    //     {
    //         Position += speed * Orientation;
            
    //     }
    //     if (event.key.keysym.sym == SDLK_a)
    //     {
    //         Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    //     }
    //     if (event.key.keysym.sym == SDLK_s)
    //     {
    //         Position += speed * -Orientation;
    //     }
    //     if (event.key.keysym.sym == SDLK_d)
    //     {
    //         Position += speed * glm::normalize(glm::cross(Orientation, Up));
    //     }
    //     if (event.key.keysym.sym == SDLK_SPACE)
    //     {
    //         Position += speed * Up;
    //     }
    //     if (event.key.keysym.sym == SDLK_LSHIFT)
    //     {
    //         Position += speed * -Up;
    //     }

    // }

    
    //handling mouse stuff

    
    if(event.type == SDL_MOUSEMOTION)
    {
        double mouseX = event.motion.x;
	    double mouseY = event.motion.y;

        //std::cout<< "x:"<<mouseX<<" y:"<<mouseY << std::endl;

        float rotX =  sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY =  sensitivity * (float)(mouseX - (width / 2)) / width;

        //std::cout<< "rotX:"<<rotX<<" rotY:"<<rotY << std::endl;

        // Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// // Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        SDL_WarpMouseInWindow(sdl_window, width/2, height/2);
    }

    

    // // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
    // // and then "transforms" them into degrees 
    // float rotX =  sensitivity * (float)(mouseY - (height / 2)) / height;
    // float rotY =  sensitivity * (float)(mouseX - (width / 2)) / width;

    //std::cout<< "rotX:"<<rotX<<" rotY:"<<rotY << std::endl;

    // Rotates the Orientation left and right
    //Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);


    //getting a value that tells us by how much our mouse moved reletive to the center
    //int xrel = event.motion.xrel;
    //int yrel = event.motion.yrel;

    //std::cout<< "xrel:"<<xrel<<" yrel:"<<yrel << std::endl;

    //normalizing the values within the range of -halfLengh and +halfLength of a side
    // float maxWidth = width/2;
    // float minWidth = (width/2 * -1);
    // xrel = 2 * ((xrel - minWidth)/width) -1;

    // float maxHeight = height/2;
    // float minHeight = (height/2 * -1);
    // yrel = 2 * ((yrel - minHeight)/height) -1;



    // Rotates the Orientation left and right
	//Orientation = glm::rotate(Orientation, glm::radians(xrel), Up);



    //std::cout<< "x:"<<mouseX<<" y:"<<mouseY << std::endl;

    // float rotX = xrel * sensitivity; //CameraYaw
	// float rotY = yrel * sensitivity; //CameraPitch
    
    // std::cout<< "xrel:"<<xrel<<" yrel:"<<yrel << std::endl;

    

    

    // if (sdl_event.button.button == SDL_BUTTON_LEFT && sdl_event.type == SDL_MOUSEBUTTONDOWN) {
    //     SDL_ShowCursor(SDL_ENABLE);
    // }

    // if (sdl_event.button.button == SDL_BUTTON_LEFT && sdl_event.type == SDL_MOUSEBUTTONUP) {
    //     SDL_ShowCursor(SDL_DISABLE); 
    // }
    

    }
};

#endif