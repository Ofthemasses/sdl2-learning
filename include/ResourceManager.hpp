#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

class ResourceManager{
    private:
        ResourceManager();
        ResourceManager(ResourceManager const&);
        ResourceManager operator=(ResourceManager const&); // Revisit learning this

        std::unordered_map<std::string, SDL_Surface*> m_surfaces;

    public:
        static ResourceManager& GetInstance();

        SDL_Surface* GetSurface(std::string filepath);
};

#endif
