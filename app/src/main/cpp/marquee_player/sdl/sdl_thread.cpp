#include <string.h>
#include "sdl_thread.h"

using namespace uranus::sdl;
void* Run_Thread(void *data) {
    SDL_Thread* thread = (SDL_Thread *) data;
    pthread_setname_np(thread->id, thread->name);
    thread->retVal = thread->fn(thread);
}

uranus::sdl::SDL_Thread *
uranus::sdl::SDL_CreateThread(uranus::sdl::SDL_Thread *thread, int (*fn)(void *), void *data,
                              const char *name) {
    strlcpy(thread->name, name, sizeof(thread->name) - 1);
    thread->fn = fn;
    int ret = pthread_create(&thread->id, NULL, Run_Thread, thread);
    if (ret)
        return nullptr;
    return thread;
}
