#include <string>

#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"

TexturedRectangle::TexturedRectangle(SDL_Renderer& renderer, std::string filepath){
    SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
    m_texture = SDL_CreateTextureFromSurface(&renderer, surface);
    SDL_FreeSurface(surface);
}
TexturedRectangle::~TexturedRectangle(){
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::SetRectangleProperties(int x, int y, int w, int h){
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}

int TexturedRectangle::GetX(){
    return m_rectangle.x;
}

int TexturedRectangle::GetY(){
    return m_rectangle.y;
}

void TexturedRectangle::SetX(int x){
    m_rectangle.x = x; 
}

void TexturedRectangle::SetY(int y){
    m_rectangle.y = y;
}

void TexturedRectangle::SetWidth(int w){
    m_rectangle.w = w;
}

void TexturedRectangle::SetHeight(int h){
    m_rectangle.h = h;
}

void TexturedRectangle::SetBlendMode(SDL_Renderer& renderer, SDL_BlendMode bm){
    SDL_SetTextureBlendMode(m_texture, bm);
}

void TexturedRectangle::Update(){}

void TexturedRectangle::Render(SDL_Renderer& renderer){
    SDL_RenderCopy(&renderer, m_texture, NULL, &m_rectangle);
}
