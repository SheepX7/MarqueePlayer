#include <jni.h>
#include <unistd.h>
#include "marquee_player/ff_player.h"
#include "marquee_player/marquee_player.h"
#include "marquee_player/marquee_log.h"
#include "marquee_jni.h"


using namespace uranus::marquee;

static JavaVM *g_jvm;
static pthread_once_t once_init = PTHREAD_ONCE_INIT;
static pthread_key_t g_thread_key;

void open(JNIEnv *env, jobject js, jstring path) {
    DEBUG_D("%s\n", __func__ );
    MarqueePlayer *marqueePlayer = new MarqueePlayer();
    marqueePlayer->ffPlayer = new FFPlayer();
    marqueePlayer->ffPlayer->audio_dev = 3;

    const char *path_c = env->GetStringUTFChars(path, 0);
    marqueePlayer->open(path_c);
}

static const char *kNativeMarqueePlayerClassName = "com/uranus/marqueeplayer/core/MarqueePlayer";
static JNINativeMethod kMarqueePlayerMethods[] = {
        {"native_open","(Ljava/lang/String;)V", (void *) open},
};

inline int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *nativeMethod, int methodsCount) {
    jclass javaCls = env->FindClass(className);

    if (!javaCls) {
        DEBUG_D("Can`t find java class: %s", className);
        return JNI_FALSE;
    }

    if (env->RegisterNatives(javaCls, nativeMethod, methodsCount) < 0) {
        DEBUG_D("Can`t register native methods, class name: %s, method count: %d", className, methodsCount);
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

int registerMarqueePlayerNativeFunctions(JavaVM *vm, JNIEnv *env) {
    if (!registerNativeMethods(env, kNativeMarqueePlayerClassName, kMarqueePlayerMethods,
                               sizeof(kMarqueePlayerMethods) / sizeof(kMarqueePlayerMethods[0])))
        return JNI_FALSE;

    g_jvm = vm;
    return JNI_TRUE;
}

static void SDL_JNI_DetachThreadEnv(void* value){
    JNIEnv *env = (JNIEnv*) value;
    if (env != NULL) {
        DEBUG_D("%s: [%d] didn't call SDL_JNI_DetachThreadEnv() explicity\n", __func__, (int)gettid());
        g_jvm->DetachCurrentThread();
        pthread_setspecific(g_thread_key, NULL);
    }
}

static void create_once_key() {
    pthread_key_create(&g_thread_key, SDL_JNI_DetachThreadEnv);
}

jint SDL_JNI_SetupThreadEnv(JNIEnv **p_env) {
    JavaVM *vm = g_jvm;
    if (!vm) {
        DEBUG_D("JavaVM is null.");
        return -1;
    }

    pthread_once(&once_init, create_once_key);
    JNIEnv *env = (JNIEnv*) pthread_getspecific(g_thread_key);
    if (env) {
        *p_env = env;
        return 0;
    }

    if (g_jvm->AttachCurrentThread(&env, NULL) == JNI_OK) {
        *p_env = env;
        pthread_setspecific(g_thread_key, env);
        return 0;
    }

    return -1;
}