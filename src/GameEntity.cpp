#include "GameEntity.hpp"
#include "Collider2D.hpp"
#include "ResourceManager.hpp"

GameEntity::GameEntity() {
    m_sprite = nullptr;
}
GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath){
    m_renderer = renderer;
    m_sprite = new TexturedRectangle(*m_renderer, spritepath);
}
GameEntity::~GameEntity(){
    if(nullptr != m_sprite){
        delete m_sprite;
    }
    for (int i = 0; i < m_colliders.size(); i++) {
        delete m_colliders[i];
    }
}

void GameEntity::RebindRenderer(SDL_Renderer* renderer){
    m_renderer = renderer;
}

void GameEntity::Update(){
    // Update the position of our collider to be
    // the same as the position of our Sprite component
    //if(nullptr != m_collider){
    //    int x  = m_sprite->GetX();
    //    int y  = m_sprite->GetY();
    //    int w  = m_sprite->GetWidth();
    //    int h  = m_sprite->GetHeight();
    //    m_collider->SetAbsolutePosition(x,y);
    //    m_collider->SetDimensions(w,h);
    //}
}

void GameEntity::AutoBoxUpdate(){
    if(nullptr != m_colliders[0]){
        int x  = m_sprite->GetX();
        int y  = m_sprite->GetY();
        int w  = m_sprite->GetWidth();
        int h  = m_sprite->GetHeight();
        m_colliders[0]->SetAbsolutePosition(x,y);
        m_colliders[0]->SetDimensions(w,h);
    }
}

void GameEntity::Render(){
    if(nullptr != m_sprite){
        m_sprite->Render(*m_renderer);
    }
    for (int i = 0; i < m_colliders.size(); i++){
        if(nullptr != m_colliders[i]){
            SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(m_renderer, &m_colliders[i]->GetColliderBoundingBox());
        }
    }
}

void GameEntity::AddBoxCollider2D(){
    m_colliders.push_back(new BoxCollider2D());
}

TexturedRectangle* GameEntity::GetSprite(){
    return m_sprite;
}

BoxCollider2D* GameEntity::GetBoxCollider2D(size_t index){
    return m_colliders[index];
}

Vector2D GameEntity::AutoBoxCollider2D(size_t index, Uint8 r, Uint8 g, Uint8 b){
    SDL_Surface* surface = ResourceManager::GetInstance().GetSurface(m_sprite->getImageFilePath());
    return m_colliders[index]->SetBoundingBoxAutomatically(surface, r,g,b);
}

void GameEntity::SetPosition(int x, int y){
    if (nullptr != m_sprite){
        m_sprite->SetPosition(x,y);
    }
    for (int i = 0; i < m_colliders.size(); i++){
        if (nullptr != m_colliders[i]){
            m_colliders[i]->SetAbsolutePosition(x,y);
        }
    }
}

void GameEntity::SetDimensions(int w, int h){
    if (nullptr != m_sprite){
        m_sprite->SetDimensions(w,h);
    }
    for (int i = 0; i < m_colliders.size(); i++){
        if (nullptr != m_colliders[i]){
            m_colliders[i]->SetDimensions(w,h);
        }
    }
}
