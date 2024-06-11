#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "shaderClass.h"
//#include <GLFW/glfw3.h>



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
    GLuint VAO; //Vertex Array Object (To Store VBOs)
    GLuint VBO; //Vertex Buffer Object
    GLuint EBO; //Index/Element Buffer Object
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


    //======create vao, vbo, ebo vars======
    //create vao
    glGenVertexArrays(1, &VAO);

    //creating a vbo
    glGenBuffers(1, &VBO);

    //creating a ebo
    glGenBuffers(1, &EBO);


    //================vbo data config================

    //making our VBO active 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Add data into the currently active VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //making our VBO inactive 
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    //============EBO data config===============================

    //making our EBO active 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    // Add data into the currently active EBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //making our EBO inactive 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




    //===============setting VAO attributes for VBO==============


    //making our VAO active
    glBindVertexArray(VAO);

    //making our VBO active again so the VAO can use it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    /* Position attribute */
    glVertexAttribPointer(      // tells currently selected VAO what to do with the supplied array data
        0,                      // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                      // size
        GL_FLOAT,               // type
        GL_FALSE,               // Tells opengl that the attributes are between 0-1
        7 * sizeof(GLfloat),    // stride
        (GLvoid*)0              // array buffer offset
        );

    glEnableVertexAttribArray(0);// enable vertex attribute 0 for currently defined pointer

    // return back to noral state
    //glDisableVertexAttribArray(0); // tell OpenGL to not use vertex attribute arrays

    
    glBindVertexArray(0); //Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind VBO


    //===============setting VAO attributes for EBO==============


    //making our VAO active
    glBindVertexArray(VAO);
    
    //making our VBO active again so the VAO can use it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //making our EBO active again so the VAO can use it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    

    /* Color attribute */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // enable vertex attribute 1 for currently defined pointer

    // return back to noral state
    //glDisableVertexAttribArray(1); // tell OpenGL to not use vertex attribute arrays
    glBindVertexArray(0); //Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind EBO (don't unbind the EBO before unbinding your VAO)
    


    //======main loop======

    

	while(main_loop){

        // Setting attributes that only work inside the main loop
        // glEnable (GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        //making our VBO active 
        glBindVertexArray(VAO);
        
        // Draw the triangle directly using buffers
        //glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        
        //draw our tringle using elements
        glDrawElements(
            GL_TRIANGLES,                           //premetive
            sizeof(indices)/sizeof(indices[0]),     //count of indices
            GL_UNSIGNED_INT,                        // datatype of our values
            0                                       //index of our indices
        );

        glBindVertexArray(0);

        

        Uint64 end = SDL_GetPerformanceCounter();

        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	    // Cap to 60 FPS
	    SDL_Delay(floor(16.666f - elapsedMS));

        SDL_GL_SwapWindow(sdl_window); //VERY VERY IMPORTANT


	}

	// clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.Delete();
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;

}
