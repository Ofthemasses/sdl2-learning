#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL2/SDL.h>

class Collider2D{
    public:
        Collider2D(){
            m_colliderRectangle.x = 0;
            m_colliderRectangle.y = 0;
            m_colliderRectangle.w = 0;
            m_colliderRectangle.h = 0;
        }

        ~Collider2D(){}

        SDL_Rect& GetColliderBoundingBox(){
            return m_colliderRectangle;
        }
        SDL_bool IsColliding(Collider2D& collider) {
            const SDL_Rect temp = collider.m_colliderRectangle;
            return SDL_HasIntersection(&m_colliderRectangle, &temp);
        }

        void SetAbsolutePosition(int x, int y){
            m_colliderRectangle.x = x;
            m_colliderRectangle.y = y;
        }

        void SetDimensions(int w, int h){
            m_colliderRectangle.w = w;
            m_colliderRectangle.h = h;
        }

        void Update(){
            // not really needed, for consistency of API
        }

        void Render(){

        }

    private:
        SDL_Rect m_colliderRectangle;
};

#endif
