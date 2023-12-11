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
#include "SDLApp.hpp"

// One possibility of creating as a global our app
SDLApp* app;

// Create objects to render
// Eventually, we will want some sort of factory
// to manage object creation in our App..
TexturedRectangle* rectangle;
TexturedRectangle* rectangle2;
TexturedRectangle* rectangle3;
TexturedRectangle* rectangle4;
TexturedRectangle* redRec;
TexturedRectangle* redRec2;
SDL_Texture* textureText;
SDL_Rect textRect;
AnimatedSprite* animatedSprite;

void SetPixel(SDL_Surface* surface, unsigned int x, unsigned int y, uint8_t r, uint8_t g, uint8_t b){
    SDL_LockSurface(surface);
    std::cout << "left mouse was pressed (" << x << "," << y << ")\n";
    uint8_t* pixels = (uint8_t*)surface->pixels;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel] = b;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel + 1] = g;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel + 2] = r;
    SDL_UnlockSurface(surface);
}

void HandleEvents(){
    SDL_Renderer* renderer = app->GetRenderer();
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        // Handle each specific event
        // Should be replaced with switch statement
        if(event.type == SDL_QUIT){
            app->StopAppLoop();
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                rectangle3->SetBlendMode(*renderer, SDL_BLENDMODE_ADD);
                rectangle4->SetBlendMode(*renderer, SDL_BLENDMODE_ADD);
            }
            else if(event.button.button == SDL_BUTTON_RIGHT){
                rectangle3->SetBlendMode(*renderer, SDL_BLENDMODE_BLEND);
                rectangle4->SetBlendMode(*renderer, SDL_BLENDMODE_BLEND);
            }
        }
        else {
            rectangle3->SetBlendMode(*renderer, SDL_BLENDMODE_MOD);
            rectangle4->SetBlendMode(*renderer, SDL_BLENDMODE_MOD);
        }
    }
}

void HandleRendering(){
    SDL_Renderer* renderer = app->GetRenderer();
    // Start our event loop
    // Give us a clear "canvas"
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // int w,h;
    // SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    // Change this at some point, it is a hack to slow down the sim
    SDL_Delay(20);

    rectangle->SetX(rectangle->GetX()+1+1/3);
    if (rectangle->GetX() > 639){
        rectangle->SetX(-639);
    }
    rectangle2->SetX(rectangle2->GetX()+1+1/3);
    if (rectangle2->GetX() > 639){
        rectangle2->SetX(-639);
    }

    rectangle3->SetY(rectangle3->GetY()+1);
    if (rectangle3->GetY() > 479){
        rectangle3->SetY(-480);
    }
    rectangle4->SetY(rectangle4->GetY()+1);
    if (rectangle4->GetY() > 479){
        rectangle4->SetY(-480);
    }
    // Do our drawing
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    redRec2->SetX(app->GetMouseX());
    redRec2->SetY(app->GetMouseY());

    if (redRec->IsColliding(*redRec2)){
        std::cout << "redRec is colliding with redRec2" << std::endl;
    }
    // SDL_RenderDrawRect(renderer,&rectangle);
    rectangle->Render(*renderer);
    rectangle2->Render(*renderer);
    rectangle3->Render(*renderer);
    rectangle4->Render(*renderer);
    redRec->Render(*renderer);
    redRec2->Render(*renderer);
    SDL_RenderCopy(renderer, textureText, NULL, &textRect);

    static int frameNumber = 0;

    animatedSprite->PlayFrame(0,0,64,64,frameNumber);
    animatedSprite->Render(renderer);
    frameNumber = (frameNumber + 1) % 7;

    // Finally show what we've drawn
    SDL_RenderPresent(renderer);

    SDL_Delay(50);
    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    //
    //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //SDL_GL_SwapWindow(window);

}

int main(int argc, char* argv[]){
    const char* title = "New SDL2 Abstraction";
    app = new SDLApp(title, 20, 20, 640, 480);
    SDL_Renderer* renderer = app->GetRenderer();
    

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

    rectangle = new TexturedRectangle(*renderer, "./assets/images/water1.bmp");
    rectangle->SetRectangleProperties(0,0,640,480);
    
    rectangle2 = new TexturedRectangle(*renderer, "./assets/images/water1.bmp");
    rectangle2->SetRectangleProperties(-639, 0, 640, 480);

    
    rectangle3 = new TexturedRectangle(*renderer, "./assets/images/water2.bmp");
    rectangle3->SetRectangleProperties(0,0,640,480);

    rectangle4 = new TexturedRectangle(*renderer, "./assets/images/water2.bmp");
    rectangle4->SetRectangleProperties(0,-480,640,480);

    redRec = new TexturedRectangle(*renderer, "./assets/images/Red.bmp");
    redRec->SetRectangleProperties(300,220,40,40);

    redRec2 = new TexturedRectangle(*renderer, "./assets/images/Red.bmp");
    redRec2->SetRectangleProperties(0,0,40,40);

    textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_FreeSurface(surfaceText);

    animatedSprite = new AnimatedSprite(renderer, "./assets/images/Mage.bmp"); 
    animatedSprite->Draw(576,416,64,64);


    //screen = SDL_GetWindowSurface(window);

    // Create a rectangle
    
    textRect.x = 42;
    textRect.y = 42;
    textRect.w = 512;
    textRect.h = 64;


    app->SetRenderCallback(HandleRendering);
    // Gives YCM error "No viable conversion from 'void ()' to 'std::function<void ()>'"
    app->SetEventCallback(HandleEvents);

    app->RunLoop();

    
    bool gameIsRunning = true;
    

    SDL_DestroyTexture(textureText);

        
    return 0;
}
