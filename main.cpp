// Comp command
// g++ main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl

// C++ Standard Libraries
#include <iostream>

// Third-party library
#include <SDL2/SDL.h>

// Include GLAD
#include <glad/glad.h>


int main(int argc, char* argv[]){

    // Create a window data type
    SDL_Window* window = nullptr;

    // Grab the window surface
    SDL_Surface* screen;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
            SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }
    // Before we create our window, specify OpenGL version
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    window = SDL_CreateWindow("C++ SDL2 Window",
            0,
            0,
            640,
            480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    screen = SDL_GetWindowSurface(window);

    SDL_Surface* image;
    image = SDL_LoadBMP("./images/w3c_home.bmp");
    SDL_BlitSurface(image,NULL,screen,NULL);
    SDL_FreeSurface(image);
    SDL_UpdateWindowSurface(window);
    

    // OpenGL setup the graphics context
    //SDL_GLContext context;
    //context = SDL_GL_CreateContext(window);

    // Setup function pointers
    //gladLoadGLLoader(SDL_GL_GetProcAddress);

    bool gameIsRunning = true;
    while(gameIsRunning){
        //glViewport(0,0,640,480);
        
        SDL_Event event;
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            // Should be replaced with switch statement
            if(event.type == SDL_QUIT){
                gameIsRunning = false;
            }
            if(event.type == SDL_MOUSEMOTION){
                std::cout << "mouse has been moved\n";
            }
            if(event.type == SDL_KEYDOWN){
                std::cout << "a key has been pressed\n";
                if(event.key.keysym.sym == SDLK_0){
                    std::cout << "0 was pressed\n";
                } else {
                    std::cout << "0 was not pressed\n";
                }
            }
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]){
                std::cout << "right arrow key is being pressed\n";
            }
        }

        //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //SDL_GL_SwapWindow(window);

    }
    SDL_DestroyWindow(window);

    SDL_Quit();
        
    return 0;
}
