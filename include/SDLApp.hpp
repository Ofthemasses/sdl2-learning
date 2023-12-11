#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <functional>

#include <SDL2/SDL.h>

// Include Font Library
#include <SDL2/SDL_ttf.h>

class SDLApp {
    public:
        SDLApp(const char* title, int x, int y, int w, int h);

        ~SDLApp();

        void SetEventCallback(std::function<void(void)> func);

        void SetRenderCallback(std::function<void(void)> func);

        void RunLoop();

        void StopAppLoop();

        SDL_Renderer* GetRenderer() const;

        int GetMouseX();

        int GetMouseY();

    private:
        // Pointer to our SDL Window
        SDL_Window* m_window = nullptr;
        // Pointer to our SDL renderer
        SDL_Renderer* m_renderer = nullptr;
        // Infinite loop for our application
        bool m_gameIsRunning = true;
        // Store our callback function
        std::function<void(void)> m_EventCallback;
        std::function<void(void)> m_RenderCallback;
        // Mouse coordinates
        int m_mouseX;
        int m_mouseY;

};

#endif
