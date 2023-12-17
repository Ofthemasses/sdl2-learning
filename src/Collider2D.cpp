#include "Collider2D.hpp"

BoxCollider2D::BoxCollider2D(){
    m_colliderRectangle.x = 0;
    m_colliderRectangle.y = 0;
    m_colliderRectangle.w = 0;
    m_colliderRectangle.h = 0;
}

BoxCollider2D::~BoxCollider2D(){}

SDL_Rect& BoxCollider2D::GetColliderBoundingBox(){
    return m_colliderRectangle;
}
SDL_bool BoxCollider2D::IsColliding(BoxCollider2D& collider) {
    const SDL_Rect temp = collider.m_colliderRectangle;
    return SDL_HasIntersection(&m_colliderRectangle, &temp);
}

void BoxCollider2D::SetAbsolutePosition(int x, int y){
    m_colliderRectangle.x = x;
    m_colliderRectangle.y = y;
}

void BoxCollider2D::SetDimensions(int w, int h){
    m_colliderRectangle.w = w;
    m_colliderRectangle.h = h;
}

Vector2D BoxCollider2D::SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b){
    SDL_LockSurface(surface);
    int w = surface->w;
    int h = surface->h;
    int pitch = surface->pitch;
    int colorchannels = pitch/w; // typically 3 or 4
    // Important to get the correct pixel type here
    Uint8* pixels = (Uint8*)surface->pixels;

    SDL_UnlockSurface(surface);

    int xmin = w;
    int xmax = 0;
    int ymin = h;
    int ymax = 0;

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w*colorchannels; x+=colorchannels){
            if (!(pixels[y*(w*colorchannels)+x+0] == b &&
                pixels[y*(w*colorchannels)+x+1] == g &&
                pixels[y*(w*colorchannels)+x+2] == r)) {

                xmin = std::fmin(x, xmin);
                xmax = std::fmax(x, xmax);

                ymin = std::fmin(ymin, y);
                ymax = std::fmax(ymax, y);
            }
        }
    }

    int scale = (1200/300);
    m_colliderRectangle.w = ((xmax/colorchannels - xmin/colorchannels)/(scale));
    m_colliderRectangle.h = (ymax-ymin)/scale;

    Vector2D result;
    result.x = xmin/(colorchannels*scale);
    result.y = ymin/scale;
    return result;
}

void BoxCollider2D::Update(){
    // not really needed, for consistency of API
}

void BoxCollider2D::Render(){

}
