#include <string>
#include <iostream>

#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"

TexturedRectangle::TexturedRectangle(SDL_Renderer& renderer, std::string filepath){
    SDL_Surface* surface = ResourceManager::GetInstance().GetSurface(filepath);
    m_texture = SDL_CreateTextureFromSurface(&renderer, surface);
    // Resource Manager should Free Resources
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

int TexturedRectangle::GetWidth(){
    return m_rectangle.w;
}

int TexturedRectangle::GetHeight(){
    return m_rectangle.h;
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
