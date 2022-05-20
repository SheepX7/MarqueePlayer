
#ifndef MARQUEEPLAYER_SDL_AUDIOSPEC_H
#define MARQUEEPLAYER_SDL_AUDIOSPEC_H

#include <cstdint>

namespace uranus {
    namespace sdl {

        const int SDL_AUDIO_ALLOW_FREQUENCY_CHANGE = 0x00000001;
        const int SDL_AUDIO_ALLOW_CHANNELS_CHANGE = 0x00000004;

        enum SDL_AudioFormat {
            AUDIO_S16SYS,
        };

        class SDL_AudioSpec {
        public:
            int channels;
            int freq;
            void *userdata;
            SDL_AudioFormat format;
            uint8_t silence;
            uint16_t samples;
            int size;

            void (*callback)(void *userdata, uint8_t *stream, int len);
        };


        int SDL_OpenAudioDevice(char const *device,
                                       int iscapture,
                                       SDL_AudioSpec* desired,
                                       SDL_AudioSpec* obtained,
                                       int allowed_changes);
    }
}


#endif //MARQUEEPLAYER_SDL_AUDIOSPEC_H
