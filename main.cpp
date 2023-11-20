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
    }
    SDL_DestroyWindow(window);

    SDL_Quit();
        
    return 0;
}
