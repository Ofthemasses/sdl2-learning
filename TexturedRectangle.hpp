#include <string>

#include <SDL2/SDL.h>

class TexturedRectangle{
    public:
        // Maybe assign the current renderer?
        TexturedRectangle(SDL_Renderer& renderer, std::string filepath);
        ~TexturedRectangle();

        void SetRectangleProperties(int x, int y, int w, int h);

        int GetX();

        int GetY();

        void SetX(int x);

        void SetY(int y);

        void SetWidth(int w);

        void SetHeight(int h);

        void SetBlendMode(SDL_Renderer& renderer, SDL_BlendMode bm);

        void Update();

        void Render(SDL_Renderer& renderer);

    private:
       SDL_Rect m_rectangle;
       SDL_Texture* m_texture;
};
