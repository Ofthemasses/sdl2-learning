#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <string>

#include <SDL2/SDL.h>
#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"

class GameEntity {
    public:
        GameEntity();
        GameEntity(SDL_Renderer* renderer, std::string spritepath);

        ~GameEntity();

        void RebindRenderer(SDL_Renderer* renderer);

        void Update();

        void Render();

        TexturedRectangle* GetSprite();

        Collider2D* GetCollider2D();

    private:
       TexturedRectangle* m_sprite;
       Collider2D* m_collider;
       SDL_Renderer* m_renderer;
};

#endif
