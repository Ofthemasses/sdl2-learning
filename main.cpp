// Comp command
// g++ main.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -ldl

// C++ Standard Libraries
#include <iostream>

// Third-party library
#include <SDL2/SDL.h>

// Include GLAD
#include <glad/glad.h>

void SetPixel(SDL_Surface* surface, unsigned int x, unsigned int y, uint8_t r, uint8_t g, uint8_t b){
    SDL_LockSurface(surface);
    std::cout << "left mouse was pressed (" << x << "," << y << ")\n";
    uint8_t* pixels = (uint8_t*)surface->pixels;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel] = b;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel + 1] = g;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel + 2] = r;
    SDL_UnlockSurface(surface);
}

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

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //screen = SDL_GetWindowSurface(window);

    //SDL_Surface* image;
    //image = SDL_LoadBMP("./images/w3c_home.bmp");
    //SDL_BlitSurface(image,NULL,screen,NULL);
    //SDL_FreeSurface(image);
    //SDL_UpdateWindowSurface(window);
    

    // OpenGL setup the graphics context
    //SDL_GLContext context;
    //context = SDL_GL_CreateContext(window);

    // Setup function pointers
    //gladLoadGLLoader(SDL_GL_GetProcAddress);

    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 20;
    rectangle.h = 20;
    bool gameIsRunning = true;
    while(gameIsRunning){
        //glViewport(0,0,640,480);
        
        SDL_Event event;

        int x,y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x, &y);
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            // Should be replaced with switch statement
            if(event.type == SDL_QUIT){
                gameIsRunning = false;
            }
//            if(event.button.button == SDL_BUTTON_LEFT){
//               SetPixel(screen, x, y, 255, 0 ,0);
//            }
//            if(event.button.button == SDL_BUTTON_RIGHT){
//               SetPixel(screen, x, y, 0 , 0, 255);
//            }
                
            // Give us a clear "canvas"
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            // Do our drawing
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, 5, 5, 100, 120);
            SDL_RenderDrawRect(renderer,&rectangle);

            // Finally show what we've drawn
            SDL_RenderPresent(renderer);
       }

       SDL_UpdateWindowSurface(window);

        //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //SDL_GL_SwapWindow(window);

    }
    SDL_DestroyWindow(window);

    SDL_Quit();
        
    return 0;
}
