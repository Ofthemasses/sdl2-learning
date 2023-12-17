#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL2/SDL.h>
#include "Vector2D.hpp"

class ICollider2D{
    public:
        virtual void Update()=0;
        virtual void Render()=0;
};

class BoxCollider2D : public ICollider2D {
    public:
        BoxCollider2D();

        ~BoxCollider2D();

        SDL_Rect& GetColliderBoundingBox();

        SDL_bool IsColliding(BoxCollider2D& collider);

        void SetAbsolutePosition(int x, int y);

        void SetDimensions(int w, int h);

        Vector2D SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b);

        void Update();

        void Render();

    private:
        SDL_Rect m_colliderRectangle;
};

#endif
