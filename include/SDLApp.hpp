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
        
        void SetUpdateCallback(std::function<void(void)> func);

        void SetRenderCallback(std::function<void(void)> func);

        void RunLoop();

        // Set the maximum render rate of each frame
        // This is a frame cap in terms of milliseconds that
        // each iteration of our main loop will not exceed.
        void SetMaxFrameRate(int fr);

        void StopAppLoop();

        SDL_Renderer* GetRenderer() const;

        int GetMouseX();

        int GetMouseY();

        int GetWindowWidth();

        int GetWindowHeight();

    private:
        // Pointer to our SDL Window
        SDL_Window* m_window = nullptr;
        // Pointer to our SDL renderer
        SDL_Renderer* m_renderer = nullptr;
        // Set the maximum frame cap
        int m_maxFrameRate;
        // Infinite loop for our application
        bool m_gameIsRunning = true;
        // Store our callback function
        std::function<void(void)> m_EventCallback;
        std::function<void (void)> m_UpdateCallback;
        std::function<void(void)> m_RenderCallback;
        // Mouse coordinates
        int m_mouseX;
        int m_mouseY;
        // Window dimensions;
        int m_width;
        int m_height;

};

#endif
