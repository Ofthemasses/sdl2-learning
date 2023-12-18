#include "Sound.hpp"

#include <iostream>

Sound::Sound(std::string filepath){
    if (SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr){
        std::cerr << "sound loading error: " << SDL_GetError() << std::endl;
    }
}

Sound::~Sound(){
    SDL_FreeWAV(m_waveStart);
    SDL_CloseAudioDevice(m_device);
}

void Sound::PlaySound(){
    // Queue the audio (play when available)
    // Can use AudioSpec callback instead for seperate thread handling
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength); // Why are we saving this var
    SDL_PauseAudioDevice(m_device, 0);
}

void Sound::StopSound(){
    SDL_PauseAudioDevice(m_device, 1);
}

void Sound::SetupDevice(){
    // Request system suitable default device
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    // Error message if no suitable device is found to play audio
    if (m_device == 0){
        std::cerr << "sound device error: " << SDL_GetError() << std::endl;
    }
}
