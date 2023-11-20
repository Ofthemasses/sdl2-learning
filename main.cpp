// C++ Standard Libraries
#include <iostream>

// Third-party library
#include <SDL2/SDL.h>


int main(int argc, char* argv[]){

    // Create a window data type
    SDL_Window* window = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
            SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("C++ SDL2 Window",
            0,
            0,
            640,
            480,
            SDL_WINDOW_SHOWN);

    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning = false;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
        
    return 0;
}
