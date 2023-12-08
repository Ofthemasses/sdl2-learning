#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager(){
}

ResourceManager::ResourceManager(ResourceManager const&){
}


ResourceManager ResourceManager::operator=(ResourceManager const& rhs){
    return *this;
}

// Instantiate exactly one instance of our class (Singleton)
ResourceManager& ResourceManager::GetInstance(){
    static ResourceManager* s_instance = new ResourceManager;
    // Return the reference to the ResourceManager so it can't be edited
    return *s_instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath){
    // We will look through our m_surface, which is a 'unordered_map' and
    // see if a file exists.
    // And if the file does exist, then return the associated surface.

    auto search = m_surfaces.find(filepath); // What is auto? Research this.
    if(search == m_surfaces.end()){
        std::cout << "Image loaded: " << filepath.c_str() << std::endl;
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        m_surfaces.insert(std::make_pair(filepath, surface));
    }

    return m_surfaces[filepath];
}
