//
// Created by Mico on 2022/5/19.
//

#include "android_audiotrack.h"
extern "C" {
#include "AudioTrack.h"
}

using namespace system;
typedef struct AudioChannelMapEntry {
    uint8_t sdl_channel;
    int android_channel;
    const char *sdl_name;
    const char *android_name;
} AudioChannelMapEntry;

static AudioChannelMapEntry g_audio_channel_map[] = {
        { 2, SDL_Android_AudioTrack_Spec::CHANNEL_OUT_STEREO, "2-chan", "CHANNEL_OUT_STEREO" },
        { 1, SDL_Android_AudioTrack_Spec::CHANNEL_OUT_MONO, "1-chan", "CHANNEL_OUT_MONO" },
};

static SDL_Android_AudioTrack_Spec::ChannelConfig find_android_channel(int sdl_channel) {
    return SDL_Android_AudioTrack_Spec::CHANNEL_OUT_MONO;
}

static int find_sdl_channel(int sdl_channel) {
    return SDL_Android_AudioTrack_Spec::CHANNEL_OUT_MONO;
}

static SDL_AudioFormat find_sdl_format(int sdl_channel) {
    return SDL_AudioFormat::AUDIO_S16SYS;
}

static SDL_Android_AudioTrack_Spec::AudioFormat find_android_format(int sdl_channel) {
    return SDL_Android_AudioTrack_Spec::ENCODING_INVALID;
}



static SDL_Android_AudioTrack* SDL_Android_AudioTrack_new_from_spec(JNIEnv *env, SDL_Android_AudioTrack_Spec *spec) {
    switch (spec->channel_config) {
        case SDL_Android_AudioTrack_Spec::CHANNEL_OUT_MONO:
            break;
    }

    SDL_Android_AudioTrack *audioTrack = new SDL_Android_AudioTrack();
    audioTrack->spec = *spec;
    audioTrack->thiz = J4AC_android_media_AudioTrack__AudioTrack(
            env, (jint) spec->stream_type, (jint) spec->sample_rate_in_hz, (jint) spec->channel_config,
            (jint) spec->audio_format, (jint) spec->buffer_size_in_bytes, (jint) spec->mode);
    return audioTrack;
}

SDL_Android_AudioTrack *
system::SDL_Android_AudioTrack_new_from_sdl_spec(JNIEnv *env, SDL_AudioSpec *sdl_spec) {
    SDL_Android_AudioTrack_Spec atrack_spec;
    SDL_Android_AudioTrack_get_default_spec(&atrack_spec);
    atrack_spec.sample_rate_in_hz = sdl_spec->freq;
    atrack_spec.channel_config = find_android_channel(sdl_spec->channels);
    atrack_spec.audio_format = find_android_format(sdl_spec->format);
    atrack_spec.buffer_size_in_bytes = sdl_spec->size;
    return SDL_Android_AudioTrack_new_from_spec(env, &atrack_spec);
}


static void system::SDL_Android_AudioTrack_get_default_spec(system::SDL_Android_AudioTrack_Spec *spec) {
    spec->stream_type = SDL_Android_AudioTrack_Spec::STREAM_MUSIC;
    spec->sample_rate_in_hz = 0;
    spec->channel_config = SDL_Android_AudioTrack_Spec::CHANNEL_OUT_STEREO;
    spec->audio_format = SDL_Android_AudioTrack_Spec::ENCODING_PCM_16BIT;
    spec->buffer_size_in_bytes = 0;
    spec->mode = SDL_Android_AudioTrack_Spec::MODE_STREAM;
}

void system::SDL_Android_AudioTrack_get_target_spec(SDL_Android_AudioTrack *atrack, SDL_AudioSpec *sdl_spec) {
    SDL_Android_AudioTrack_Spec atrack_spec;
    atrack_spec = atrack->spec;
    sdl_spec->freq = atrack_spec.sample_rate_in_hz;
    sdl_spec->channels= find_sdl_channel(atrack_spec.channel_config);
    sdl_spec->format = find_sdl_format(atrack_spec.audio_format);
    sdl_spec->size = atrack_spec.buffer_size_in_bytes;
}

