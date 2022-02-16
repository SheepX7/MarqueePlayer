#include <jni.h>
#include <string>
#include "marquee_player/marquee_player.h"
using namespace uranus::marquee;

extern "C" JNIEXPORT jstring JNICALL
Java_com_uranus_marqueeplayer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}