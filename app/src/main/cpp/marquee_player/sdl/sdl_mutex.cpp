//
// Created by Mico on 2022/2/28.
//

#include "sdl_mutex.h"

void uranus::sdl::SDL_DestroyMutex(uranus::sdl::SDL_mutex *mutex) {

}

uranus::sdl::SDL_mutex *uranus::sdl::SDL_CreateMutex(void) {
    SDL_mutex *mutex = new SDL_mutex();
    pthread_mutex_init(&mutex->id, NULL);
    return mutex;
}

uranus::sdl::SDL_cond *uranus::sdl::SDL_CreateCond(void) {
    SDL_cond *cond = new SDL_cond();
    pthread_cond_init(&cond->id, NULL);
    return cond;
}
