#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <string>

#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"

class GameEntity {
    public:
        GameEntity() {
            m_sprite = nullptr;
        }
        GameEntity(SDL_Renderer* renderer, std::string spritepath){
            m_renderer = renderer;
            m_sprite = new TexturedRectangle(*m_renderer, spritepath);
        }
        ~GameEntity(){}

        void RebindRenderer(SDL_Renderer* renderer){
            m_renderer = renderer;
        }

        void Update(){}

        void Render(){
            if(nullptr == m_sprite){ // Why is this safer than m_sprite == nullptr?
                m_sprite->Render(*m_renderer);
            }
        }

        TexturedRectangle* GetSprite(){
            return m_sprite;
        }

    private:
       TexturedRectangle* m_sprite;
       SDL_Renderer* m_renderer;
};

#endif
