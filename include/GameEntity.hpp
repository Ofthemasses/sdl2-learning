#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"
#include "Vector2D.hpp"

class GameEntity {
    public:
        GameEntity();
        GameEntity(SDL_Renderer* renderer, std::string spritepath);

        ~GameEntity();

        void RebindRenderer(SDL_Renderer* renderer);

        void Update();

        void AutoBoxUpdate();

        void Render();

        void AddBoxCollider2D();
        
        TexturedRectangle* GetSprite();

        BoxCollider2D* GetBoxCollider2D(size_t index);

        Vector2D AutoBoxCollider2D(size_t index, Uint8 r, Uint8 g, Uint8 b);

        void SetPosition(int x, int y);

        void SetDimensions(int w, int h);

    private:
       TexturedRectangle* m_sprite;
       std::vector<BoxCollider2D*> m_colliders;
       SDL_Renderer* m_renderer;
};

#endif
