#include <jni.h>
#include "ff_player.h"



JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    global_ffp_player_init();
    return -1;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved) {

}

