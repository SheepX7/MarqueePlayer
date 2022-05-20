#include <marquee_player/marquee_log.h>
#include <cstring>
#include <string>
#include "sdl_thread.h"

using namespace uranus::sdl;
void* Run_Thread(void *data) {
    SDL_Thread* thread = (SDL_Thread *) data;
    pthread_setname_np(thread->id, thread->name);
    thread->retVal = thread->fn(thread->data);
    DEBUG_D("thread->retVal : %d", thread->retVal);
}

uranus::sdl::SDL_Thread *
uranus::sdl::SDL_CreateThread(uranus::sdl::SDL_Thread *thread, int (*fn)(void *), void *data,
                              const char *name) {
    if (!thread) {
        DEBUG_D("create SDL thread");
        thread = new SDL_Thread();
    }

    DEBUG_D( "thread.name => %s, name -> %s, size: %d", "12", name, sizeof(thread->name));
    strlcpy(thread->name, name, sizeof(thread->name) - 1);
    DEBUG_D( "thread.name => %s, ", thread->name);

    thread->fn = fn;
    thread->data = data;
    int ret = pthread_create(&thread->id, NULL, Run_Thread, thread);
    DEBUG_D("create pthread result code: %d", ret);
    if (ret)
        return nullptr;
    return thread;
}
