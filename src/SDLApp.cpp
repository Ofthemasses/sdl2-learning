#include "SDLApp.hpp"
#include <iostream>

SDLApp::SDLApp(Uint32 subsystemFlags, const char* title, int x, int y, int w, int h){
    m_width = w;
    m_height = h;

    m_maxFrameRate = 90;

    if(SDL_Init(subsystemFlags) < 0){
        std::cout << "SDL could not be initialized: " <<
        SDL_GetError();
    } else {
        std::cout << "SDL video system is ready to go\n";
    }
    if (TTF_Init() == 1){
        std::cout << "Could not initialize SDL2 ttf, error: "
        << TTF_GetError()
        << std::endl;
    } else {
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }

    m_window = SDL_CreateWindow(title,x,y,w,h,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

SDLApp::~SDLApp(){
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLApp::SetEventCallback(std::function<void(void)> func){
    m_EventCallback = func;
}

void SDLApp::SetUpdateCallback(std::function<void(void)> func){
    m_UpdateCallback = func;
}

void SDLApp::SetRenderCallback(std::function<void(void)> func){
    m_RenderCallback = func;
}

void SDLApp::RunLoop(){
    while(m_gameIsRunning){
        Uint32 start = SDL_GetTicks();
        Uint32 buttons;
        buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
        m_EventCallback();
        m_UpdateCallback();
        m_RenderCallback(); 
        // Frame Capping (Hard Limit)
        Uint32 elapsed = SDL_GetTicks() - start;
        if (elapsed < m_maxFrameRate){
            SDL_Delay(m_maxFrameRate - elapsed);
        }

    }
}

void SDLApp::SetMaxFrameRate(int fr){
    m_maxFrameRate = fr;
}

void SDLApp::StopAppLoop() {
    m_gameIsRunning = false;
}

SDL_Renderer* SDLApp::GetRenderer() const{
    return m_renderer;
}

int SDLApp::GetMouseX(){
    return m_mouseX;
}

int SDLApp::GetMouseY(){
    return m_mouseY;
}

int SDLApp::GetWindowWidth(){
    return m_width;
}

int SDLApp::GetWindowHeight(){
    return m_height;
}
