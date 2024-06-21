#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <stdlib.h>
#include "shaderClass.h"
#include "texturedGraphicObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES   TexCoord  //
	-0.5f, 0.0f,  0.5f, 0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f, 1.0f, 1.0f,
	 0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f, 1.0f, 1.0f,
	 0.0f, 0.8f,  0.0f,	0.5f, 0.5f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};




int main(){

    //======defining usefull variables======
    
	SDL_Window* sdl_window= nullptr;
	SDL_Renderer* sdl_renderer= nullptr;
    GLint width= 640;
    GLint height= 480;
    //SDL_GLContext sdl_context;
    //SDL_Surface* sdl_surface= nullptr;
    
    bool main_loop= true;

    //======setting important sdl attributes======

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    //enable double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //set color depth for 4 chanels (24 for 3 chanels)
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 32);

    //specifies the number of multisample buffers to use for anti-aliasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);

    //used to set the number of samples used for multisample anti-aliasing (MSAA) when creating an OpenGL context.
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    
    //use alpha chanel
    glEnable(GL_BLEND); 	
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //============initializing components and testing them======
    //sdl_init(sdl_window, sdl_renderer, width, height);

    GLint success;

    success = SDL_Init(SDL_INIT_VIDEO);
    if(success < 0){
        std::cerr << "Failed to initialize SDL video" << std::endl;
        exit(-1);
    }

    success = SDL_Init(SDL_INIT_EVENTS);
    if(success < 0){
        std::cerr << "Failed to initialize SDL2 events" << std::endl;
        exit(-1);
    }

    sdl_window = SDL_CreateWindow("new window", 0, 0, width, height, 0);
    if(sdl_window == nullptr){
        std::cerr << "Failed to create SDL window" << std::endl;
        exit(-1);
    }

    //sdl_context = SDL_GL_CreateContext(sdl_window);

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(sdl_renderer == nullptr){
        std::cerr << "Failed to create SDL renderer" << std::endl;
        SDL_DestroyWindow(sdl_window);
        exit(-1);
    }

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Glew is not working properly" << std::endl;
        exit(-1);
    }


    
    
	//build and compile shader program

    Shader texturedShaderProgram = Shader("resources/shaders/textureVertexShader.glsl",
                           "resources/shaders/textureFragmentShader.glsl");


    //Declare a texture that we are going to sample from for our objects
    Texture texture1 = Texture("resources/textures/bricks/bricks12 diffuse 1k.jpg", 
                                GL_TEXTURE_2D, 
                                GL_RGB, 
                                GL_UNSIGNED_BYTE);
    
    // declare our object
    texturedGraphicObject obj1(vertices, sizeof(vertices), 
                               indices, sizeof(indices), 
                               &texturedShaderProgram
                               );

    
    Camera camera(width, height, glm::vec3(0.0f, 0.2f, 3.0f));
    
    // // Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    SDL_ShowCursor(SDL_DISABLE);
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    /*In relative mouse mode, the cursor is hidden and the mouse movements 
    are reported as relative motion from the current position. 
    This is useful for implementing first-person or other types of games 
    where mouse movements are used to control the camera or player movement.*/

    

    // const Uint8* mouseState;
	
    

    //SDL_WarpMouseInWindow(sdl_window, width/2, height/2);

    SDL_Event event;
        
    while(main_loop){
        

        // Setting attributes that only work inside the main loop
        glEnable (GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //making note of the start time
        //start = SDL_GetPerformanceCounter();

		//==========event pooling==============
        
        //initilizing variables to store data
        
        while (SDL_PollEvent(&event)){

            //std::cout << "Event type: " << event.type << std::endl;

            // if(event.type == SDL_KEYDOWN && event.key.repeat != 0)
            // {
            //     break;
            // }

            if (event.type == SDL_QUIT)
            {
                main_loop = false;
            }

            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                main_loop = false;
            }

            if (event.type == SDL_APP_LOWMEMORY)
            {
                std::cout<< "LOW MEM!!"<< std::endl;
            }

            // if (event.type == SDL_MOUSEMOTION)
            // {
            //     double mouseX = event.motion.xrel;
	        //     double mouseY = event.motion.yrel;

            //     std::cout<< "x:"<<mouseX<<" y:"<<mouseY << std::endl;

            //     SDL_WarpMouseInWindow(sdl_window, width/2, height/2);
            // }

            //handle camra movement based on events
            camera.Inputs(event, sdl_window);
            

        }

        

       


        //render section


        //clear scr
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        camera.Matrix(45.0f, 0.1f, 100.0f, texturedShaderProgram, "camMatrix");

        // // Initializes matrices so they are not the null matrix
		// glm::mat4 model = glm::mat4(1.0f); //to bring from object space to world space
		// glm::mat4 view = glm::mat4(1.0f); //to get view from a camra position
		// glm::mat4 proj = glm::mat4(1.0f); //to get perspective/get 2d representation of objects


        // // Assigns different transformations to each matrix
		// model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		// proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
        
        // // Outputs the matrices into the Vertex Shader
		// int modelLoc = glGetUniformLocation(texturedShaderProgram.shaderProgramID, "model");
		// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// int viewLoc = glGetUniformLocation(texturedShaderProgram.shaderProgramID, "view");
		// glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// int projLoc = glGetUniformLocation(texturedShaderProgram.shaderProgramID, "proj");
		// glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        //draw shape
        obj1.drawObject(&texture1, 0);


        SDL_GL_SwapWindow(sdl_window); //VERY VERY IMPORTANT

        
	}

	// clean up
    obj1.deleteObject();
    texture1.Delete();
    texturedShaderProgram.Delete();
	
    SDL_RenderClear(sdl_renderer);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);

	SDL_Quit();

	return 0;

}
