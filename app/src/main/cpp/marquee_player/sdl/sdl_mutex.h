
#include <pthread.h>

namespace uranus {
    namespace sdl {
        class SDL_mutex {
        public:
            pthread_mutex_t id;
        };

        SDL_mutex  *SDL_CreateMutex(void);
        void        SDL_DestroyMutex(SDL_mutex *mutex);
        void        SDL_DestroyMutexP(SDL_mutex **mutex);
        int         SDL_LockMutex(SDL_mutex *mutex);
        int         SDL_UnlockMutex(SDL_mutex *mutex);



        class SDL_cond {
        public:
            pthread_cond_t id;
        };

        SDL_cond   *SDL_CreateCond(void);
        void        SDL_DestroyCond(SDL_cond *cond);
        void        SDL_DestroyCondP(SDL_cond **mutex);
        int         SDL_CondSignal(SDL_cond *cond);
        int         SDL_CondBroadcast(SDL_cond *cond);
        int         SDL_CondWaitTimeout(SDL_cond *cond, SDL_mutex *mutex, uint32_t ms);
        int         SDL_CondWait(SDL_cond *cond, SDL_mutex *mutex);
    }
}