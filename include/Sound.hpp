#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>

#include <SDL2/SDL.h>

class ISound{
    public:
        virtual ~ISound() {};

        virtual void PlaySound() = 0;
        virtual void StopSound() = 0;
};

class Sound : public ISound {
    public:
        Sound(std::string filepath);

        ~Sound();

        void PlaySound();

        void StopSound();

        void SetupDevice();

    private:
        // Device the Sound will play on
        SDL_AudioDeviceID m_device;

        // Wave file properties
        SDL_AudioSpec m_audioSpec;
        Uint8* m_waveStart;
        Uint32 m_waveLength;
};

#endif
