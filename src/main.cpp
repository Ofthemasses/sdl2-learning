// Comp command
// g++ main.cpp TexturedRectangle.cpp glad/src/glad.c -I./glad/include -o prog -lSDL2 -lSDL2_ttf -ldl

// C++ Standard Libraries
#include <iostream>

// Third-party library
#include <SDL2/SDL.h>

// Include Font Library
#include <SDL2/SDL_ttf.h>

// Include GLAD, Look into re including this later
// #include <glad/glad.h>

#include "TexturedRectangle.hpp"
#include "AnimatedSprite.hpp"

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

    if (TTF_Init() == 1){
        std::cout << "Could not initialize SDL2 ttf, error: "
           << TTF_GetError()
           << std::endl;
    } else {
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }

    TTF_Font* ourFont = TTF_OpenFont("./assets/fonts/Fira_Code/FiraCode-VariableFont_wght.ttf", 128);

    if(ourFont == nullptr){
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont, "Testing TTF Rendering",
            {255,255,255});

    // It is best to add this after loading the surface as you are shipping the data
    // to the GPU.
    // SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0XFF));

    TexturedRectangle rectangle(*renderer, "./assets/images/water1.bmp");
    rectangle.SetRectangleProperties(0,0,640,480);
    
    TexturedRectangle rectangle2(*renderer, "./assets/images/water1.bmp");
    rectangle2.SetRectangleProperties(-639, 0, 640, 480);

    
    TexturedRectangle rectangle3(*renderer, "./assets/images/water2.bmp");
    rectangle3.SetRectangleProperties(0,0,640,480);

    TexturedRectangle rectangle4(*renderer, "./assets/images/water2.bmp");
    rectangle4.SetRectangleProperties(0,-480,640,480);

    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_FreeSurface(surfaceText);

    AnimatedSprite animatedSprite(renderer, "./assets/images/Mage.bmp"); 
    animatedSprite.Draw(576,416,64,64);
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
    
    SDL_Rect textRect;
    textRect.x = 42;
    textRect.y = 42;
    textRect.w = 512;
    textRect.h = 64;

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
                    rectangle3.SetBlendMode(*renderer, SDL_BLENDMODE_ADD);
                    rectangle4.SetBlendMode(*renderer, SDL_BLENDMODE_ADD);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    rectangle3.SetBlendMode(*renderer, SDL_BLENDMODE_BLEND);
                    rectangle4.SetBlendMode(*renderer, SDL_BLENDMODE_BLEND);
                }
            }
            else {
                rectangle3.SetBlendMode(*renderer, SDL_BLENDMODE_MOD);
                rectangle4.SetBlendMode(*renderer, SDL_BLENDMODE_MOD);
            }

//          if(event.button.button == SDL_BUTTON_RIGHT){
//              SetPixel(screen, x, y, 0 , 0, 255);
//          }
       }
                
       // Give us a clear "canvas"
       SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
       SDL_RenderClear(renderer);

       // int w,h;
       // SDL_QueryTexture(texture, NULL, NULL, &w, &h);
       // Change this at some point, it is a hack to slow down the sim
       SDL_Delay(20);

       rectangle.SetX(rectangle.GetX()+1+1/3);
       if (rectangle.GetX() > 639){
           rectangle.SetX(-639);
       }
       rectangle2.SetX(rectangle2.GetX()+1+1/3);
       if (rectangle2.GetX() > 639){
           rectangle2.SetX(-639);
       }

       rectangle3.SetY(rectangle3.GetY()+1);
       if (rectangle3.GetY() > 479){
           rectangle3.SetY(-480);
       }
       rectangle4.SetY(rectangle4.GetY()+1);
       if (rectangle4.GetY() > 479){
           rectangle4.SetY(-480);
       }
       // Do our drawing
       SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

       // SDL_RenderDrawRect(renderer,&rectangle);
       rectangle.Render(*renderer);
       rectangle2.Render(*renderer);
       rectangle3.Render(*renderer);
       rectangle4.Render(*renderer);
       SDL_RenderCopy(renderer, textureText, NULL, &textRect);

       static int frameNumber = 0;

       animatedSprite.PlayFrame(0,0,64,64,frameNumber);
       animatedSprite.Render(renderer);
       frameNumber = (frameNumber + 1) % 7;

       // Finally show what we've drawn
       SDL_RenderPresent(renderer);

       SDL_UpdateWindowSurface(window);

       SDL_Delay(50);
        //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //SDL_GL_SwapWindow(window);

    }

    SDL_DestroyTexture(textureText);
    
    SDL_DestroyWindow(window);

    SDL_Quit();
        
    return 0;
}
