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

    SDL_Surface* surface = SDL_LoadBMP("./images/water1.bmp");
    SDL_Surface* surface2 = SDL_LoadBMP("./images/water2.bmp");

    // It is best to add this after loading the surface as you are shipping the data
    // to the GPU.
    // SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0XFF));


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

    SDL_FreeSurface(surface);
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
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 640;
    rectangle.h = 480;

    SDL_Rect rectangle2;
    rectangle2.x = -639;
    rectangle2.y = 0;
    rectangle2.w = 640;
    rectangle2.h = 480;

    SDL_Rect rectangle3;
    rectangle3.x = 0;
    rectangle3.y = 0;
    rectangle3.w = 640;
    rectangle3.h = 480;

    SDL_Rect rectangle4;
    rectangle4.x = 0;
    rectangle4.y = -480;
    rectangle4.w = 640;
    rectangle4.h = 480;

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
//            if(event.type == SDL_MOUSEMOTION){
//                rectangle2.x = event.motion.x;
//                rectangle2.y = event.motion.y;
//            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_ADD);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_BLEND);
                }
            }
            else {
                SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_MOD);
            }

//          if(event.button.button == SDL_BUTTON_RIGHT){
//              SetPixel(screen, x, y, 0 , 0, 255);
//          }
       }
                
       // Give us a clear "canvas"
       SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
       SDL_RenderClear(renderer);

       int w,h;
       SDL_QueryTexture(texture, NULL, NULL, &w, &h);
       // Change this at some point, it is a hack to slow down the sim
       SDL_Delay(20);

       rectangle.x ++;
       if (rectangle.x > 639){
           rectangle.x = -639;
       }
       rectangle2.x ++;
       if (rectangle2.x > 639){
           rectangle2.x = -639;
       }

       rectangle3.y ++;
       if (rectangle3.y > 479){
           rectangle3.y = -480;
       }
       rectangle4.y ++;
       if (rectangle4.y > 479){
           rectangle4.y = -480;
       }
       // Do our drawing
       SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
       SDL_RenderDrawLine(renderer, 5, 5, 300, 300);
       
       // SDL_RenderDrawRect(renderer,&rectangle);
       SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
       SDL_RenderCopy(renderer, texture, NULL, &rectangle);
       SDL_RenderCopy(renderer, texture, NULL, &rectangle2);

       SDL_RenderCopy(renderer, texture2, NULL, &rectangle3);
       SDL_RenderCopy(renderer, texture2, NULL, &rectangle4);
       // Finally show what we've drawn
       SDL_RenderPresent(renderer);

       SDL_UpdateWindowSurface(window);

        //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //SDL_GL_SwapWindow(window);

    }

    SDL_DestroyTexture(texture);
    
    SDL_DestroyWindow(window);

    SDL_Quit();
        
    return 0;
}
