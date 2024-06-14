#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "shaderClass.h"
#include "graphicObjectClass.h"



GLfloat vertices[] = {
/*   Positions            Colors */
    -0.4f, -0.2f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
     0.4f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
     0.0f,  0.4f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
    -0.2f,  0.1f, 0.0f,   1.0f, 0.0f, 1.0f, 1.0f,
     0.0f, -0.2f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f,
     0.2f,  0.1f, 0.0f,   0.0f, 1.0f, 1.0f, 1.0f
};

GLuint indices[] = {
    0,4,3,
    4,1,5,
    3,5,2
};




int main(){

    //======defining usefull variables======
    
	SDL_Window* sdl_window= nullptr;
	SDL_Renderer* sdl_renderer= nullptr;
    //SDL_GLContext sdl_context;
    SDL_Event sdl_event;
    //SDL_Surface* sdl_surface= nullptr;
    GLint success;
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

    success = SDL_Init(SDL_INIT_EVENTS);
    if(success < 0){
        std::cerr << "Failed to initialize SDL2 events" << std::endl;
        return -1;
    }

	success = SDL_Init(SDL_INIT_VIDEO);
    if(success < 0){
        std::cerr << "Failed to initialize SDL video" << std::endl;
        return -1;
    }

    sdl_window = SDL_CreateWindow("new window", 0, 0, 640, 480, 0);
    if(sdl_window == nullptr){
        std::cerr << "Failed to create SDL window" << std::endl;
        return -1;
    }

    //sdl_context = SDL_GL_CreateContext(sdl_window);

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(sdl_renderer == nullptr){
        std::cerr << "Failed to create SDL renderer" << std::endl;
        SDL_DestroyWindow(sdl_window);
        return -1;
    }

    // sdl_surface = SDL_GetWindowSurface(sdl_window);
    // if(sdl_surface == nullptr){
    //     std::cerr << "Failed to create surface for SDL window" << std::endl;
    //     SDL_DestroyWindow(sdl_window);
    //     return -1;
    // }

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Glew is not working properly" << std::endl;
        return -1;
    }

	//======build and compile shader program======
    
    Shader shader = Shader("resources/shaders/defaultVertexShader.glsl",
                           "resources/shaders/defaultFragmentShader.glsl");

    shader.Activate();

    // declare our object

    graphicObject obj1(vertices, sizeof(vertices), indices, sizeof(indices));

    

	while(main_loop){

        // Setting attributes that only work inside the main loop
        glEnable (GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //making note of the start time
        Uint64 start = SDL_GetPerformanceCounter();

		//event loop
		while(SDL_PollEvent(&sdl_event) != 0){

			if (sdl_event.type == SDL_QUIT){
				main_loop = false;
			}

		}


        //render loop

        //clear scr
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT); 

        

        //draw shape
        obj1.drawObject();

        

        Uint64 end = SDL_GetPerformanceCounter();

        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	    // Cap to 60 FPS
	    SDL_Delay(floor(16.666f - elapsedMS));

        SDL_GL_SwapWindow(sdl_window); //VERY VERY IMPORTANT


	}

	// clean up
    obj1.deleteObject();
    shader.Delete();
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;

}
