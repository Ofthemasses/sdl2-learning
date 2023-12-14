#include "GameEntity.hpp"
#include "Collider2D.hpp"

GameEntity::GameEntity() {
    m_sprite = nullptr;
}
GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath){
    m_renderer = renderer;
    m_sprite = new TexturedRectangle(*m_renderer, spritepath);
    m_collider = new Collider2D();
}
GameEntity::~GameEntity(){
    if(nullptr != m_sprite){
        delete m_sprite;
    }
    if(nullptr != m_collider){
        delete m_collider;
    }
}

void GameEntity::RebindRenderer(SDL_Renderer* renderer){
    m_renderer = renderer;
}

void GameEntity::Update(){
    // Update the position of our collider to be
    // the same as the position of our Sprite component
    if(nullptr != m_collider){
        int x  = m_sprite->GetX();
        int y  = m_sprite->GetY();
        int w  = m_sprite->GetWidth();
        int h  = m_sprite->GetHeight();
        m_collider->SetAbsolutePosition(x,y);
        m_collider->SetDimensions(w,h);
    }
}

void GameEntity::Render(){
    if(nullptr != m_sprite){
        m_sprite->Render(*m_renderer);
    }
    if(nullptr != m_collider){
        SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(m_renderer, &m_collider->GetColliderBoundingBox());
    }
}

TexturedRectangle* GameEntity::GetSprite(){
    return m_sprite;
}

Collider2D* GameEntity::GetCollider2D(){
    return m_collider;
}

