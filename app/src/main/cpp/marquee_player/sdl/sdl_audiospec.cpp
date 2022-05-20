//
// Created by Mico on 2022/4/22.
//

#include "marquee_player/marquee_log.h"
#include "sdl_audiospec.h"
#include "marquee_jni.h"
#include "android_audiotrack.h"

using namespace system;
int uranus::sdl::SDL_OpenAudioDevice(char const*device, int iscapture,
                                     uranus::sdl::SDL_AudioSpec *desired,
                                     uranus::sdl::SDL_AudioSpec *obtained, int allowed_changes) {
    DEBUG_D(__func__ );
    JNIEnv *env = NULL;
    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        DEBUG_D("Can`t setup thread env");
        return 0;
    }

    SDL_Android_AudioTrack* audioTrack = SDL_Android_AudioTrack_new_from_sdl_spec(env, desired);
    if (!audioTrack) {
        DEBUG_D("Create SDL_Android_AudioTrack failed.");
        return 0;
    }

    if (obtained) {
        SDL_Android_AudioTrack_get_target_spec(audioTrack, obtained);
        DEBUG_D("audio target format fmt:0x%x, channel:0x%x", (int)obtained->format, (int)obtained->channels);
    }

    return 1;
}
