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
#include "GameEntity.hpp"
#include "Sound.hpp"
#include "SDLApp.hpp"

// One possibility of creating as a global our app
SDLApp* app;

// Create objects to render
// Eventually, we will want some sort of factory
// to manage object creation in our App..
GameEntity* rectangle;
GameEntity* rectangle2;
GameEntity* rectangle3;
GameEntity* rectangle4;
GameEntity* redRec;
GameEntity* redRec2;
SDL_Texture* textureText;
SDL_Rect textRect;
AnimatedSprite* animatedSprite; // TODO Create abstraction for multiple texture types be hooked into GameEntities
Sound* CollisionSound;

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
                if(redRec->GetBoxCollider2D(0)->IsColliding(*redRec2->GetBoxCollider2D(0))){
                    std::cout << "redRec is colliding with redRec2" << std::endl;
                    CollisionSound->PlaySound();
                }
                app->SetMaxFrameRate(4);
                rectangle3->GetSprite()->SetBlendMode(*renderer, SDL_BLENDMODE_ADD);
                rectangle4->GetSprite()->SetBlendMode(*renderer, SDL_BLENDMODE_ADD);
            }
            else if(event.button.button == SDL_BUTTON_RIGHT){
                app->SetMaxFrameRate(16);
                rectangle3->GetSprite()->SetBlendMode(*renderer, SDL_BLENDMODE_BLEND);
                rectangle4->GetSprite()->SetBlendMode(*renderer, SDL_BLENDMODE_BLEND);
            }
        }
        else {
            rectangle3->GetSprite()->SetBlendMode(*renderer, SDL_BLENDMODE_MOD);
            rectangle4->GetSprite()->SetBlendMode(*renderer, SDL_BLENDMODE_MOD);
        }
    }
}

void HandleRendering(){
    SDL_Renderer* renderer = app->GetRenderer();
    // Start our event loop
    // Give us a clear "canvas"
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    rectangle->GetSprite()->SetX(rectangle->GetSprite()->GetX()+1+1/3);
    if (rectangle->GetSprite()->GetX() > 639){
        rectangle->GetSprite()->SetX(-639);
    }
    rectangle2->GetSprite()->SetX(rectangle2->GetSprite()->GetX()+1+1/3);
    if (rectangle2->GetSprite()->GetX() > 639){
        rectangle2->GetSprite()->SetX(-639);
    }

    rectangle3->GetSprite()->SetY(rectangle3->GetSprite()->GetY()+1);
    if (rectangle3->GetSprite()->GetY() > 479){
        rectangle3->GetSprite()->SetY(-480);
    }
    rectangle4->GetSprite()->SetY(rectangle4->GetSprite()->GetY()+1);
    if (rectangle4->GetSprite()->GetY() > 479){
        rectangle4->GetSprite()->SetY(-480);
    }
    // Do our drawing
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    redRec2->GetSprite()->SetX(app->GetMouseX());
    redRec2->GetSprite()->SetY(app->GetMouseY());

    // Create moving target
    static int posX = 80;
    static int posY = 80;
    static bool up = true;
    static bool right = true;

    if (up){
        posY--;
    } else {
        posY++;
    }

    if (right){
        posX++;
    } else {
        posX--;
    }

    if(posX > app->GetWindowWidth() - 80 || posX < 80){
        right = !right;
    }

    if(posY > app->GetWindowHeight() - 80 || posY < 80){
        up = !up;
    }

    redRec->GetSprite()->SetX(posX);
    redRec->GetSprite()->SetY(posY);
    // SDL_RenderDrawRect(renderer,&rectangle);
    rectangle->GetSprite()->Render(*renderer);
    rectangle2->GetSprite()->Render(*renderer);
    rectangle3->GetSprite()->Render(*renderer);
    rectangle4->GetSprite()->Render(*renderer);
    redRec->GetSprite()->Render(*renderer);
    redRec2->GetSprite()->Render(*renderer);
    SDL_RenderCopy(renderer, textureText, NULL, &textRect);

   
    

    static int frameNumber = 0;

    animatedSprite->PlayFrame(0,0,64,64,frameNumber);
    animatedSprite->Render(renderer);
    frameNumber = (frameNumber + 1) % 7;

    // Finally show what we've drawn
    SDL_RenderPresent(renderer);

    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    //
    //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    //SDL_GL_SwapWindow(window);

}

void HandleUpdate(){
    redRec->AutoBoxUpdate();
    redRec2->AutoBoxUpdate();
}

int main(int argc, char* argv[]){
    const char* title = "New SDL2 Abstraction";
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, title, 20, 20, 640, 480);
    SDL_Renderer* renderer = app->GetRenderer();
    app->SetMaxFrameRate(16);

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

    rectangle = new GameEntity(renderer, "./assets/images/water1.bmp");
    rectangle->GetSprite()->SetRectangleProperties(0,0,640,480);
    
    rectangle2 = new GameEntity(renderer, "./assets/images/water1.bmp");
    rectangle2->GetSprite()->SetRectangleProperties(-639, 0, 640, 480);

    
    rectangle3 = new GameEntity(renderer, "./assets/images/water2.bmp");
    rectangle3->GetSprite()->SetRectangleProperties(0,0,640,480);

    rectangle4 = new GameEntity(renderer, "./assets/images/water2.bmp");
    rectangle4->GetSprite()->SetRectangleProperties(0,-480,640,480);

    redRec = new GameEntity(renderer, "./assets/images/Red.bmp");
    redRec->GetSprite()->SetRectangleProperties(300,220,40,40);
    redRec->AddBoxCollider2D();

    redRec2 = new GameEntity(renderer, "./assets/images/Red.bmp");
    redRec2->GetSprite()->SetRectangleProperties(0,0,40,40);
    redRec2->AddBoxCollider2D();

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


    CollisionSound = new Sound("./assets/sounds/qkey.wav");
    CollisionSound->SetupDevice();
    app->SetRenderCallback(HandleRendering);
    // Gives YCM error "No viable conversion from 'void ()' to 'std::function<void ()>'"
    app->SetUpdateCallback(HandleUpdate);
    app->SetEventCallback(HandleEvents);

    app->RunLoop();

    
    bool gameIsRunning = true;
    

    SDL_DestroyTexture(textureText);

        
    return 0;
}
