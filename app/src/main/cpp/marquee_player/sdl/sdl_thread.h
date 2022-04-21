#include <pthread.h>
#ifndef MARQUEEPLAYER_SDL_THREAD_H
#define MARQUEEPLAYER_SDL_THREAD_H

namespace uranus {
    namespace sdl {
        class SDL_Thread {
        public:
            pthread_t id;
            int (*fn)(void *);
            int retVal;
            char *name;
        };

        SDL_Thread* SDL_CreateThread(SDL_Thread *thread, int (*fn)(void*), void *data, const char *name);
    }
}

#endif //MARQUEEPLAYER_SDL_THREAD_H
