#include <jni.h>
#include <string>
#include <marquee_player/marquee_log.h>
#include "marquee_player/marquee_player.h"
extern "C" {
#include "marquee_player/system/AudioTrack.h"
}
using namespace uranus::marquee;

int registerMarqueePlayerNativeFunctions(JavaVM *vm, JNIEnv *env);
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6)!= JNI_OK)
        return JNI_FALSE;

    if (!registerMarqueePlayerNativeFunctions(vm, env))
        return JNI_FALSE;

    J4A_loadClass__J4AC_android_media_AudioTrack(env);
    return JNI_VERSION_1_6;
}


JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved) {

}

