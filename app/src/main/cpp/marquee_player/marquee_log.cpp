//
// Created by Mico on 2022/4/26.
//

#include "marquee_log.h"
#include <android/log.h>

const char *kMarqueePlayer = "marquee_player";
Logger::Logger() {

}

void Logger::e(const char *message, ...) {
    va_list argptr;
    va_start(argptr, message);
    __android_log_vprint(ANDROID_LOG_ERROR, kMarqueePlayer, message, argptr);
    va_end(argptr);
}

void Logger::w(const char *message, ...) {
    va_list argptr;
    va_start(argptr, message);
    __android_log_vprint(ANDROID_LOG_WARN, kMarqueePlayer, message, argptr);
    va_end(argptr);
}

void Logger::d(const char *message, ...) {
    va_list argptr;
    va_start(argptr, message);
    __android_log_vprint(ANDROID_LOG_DEBUG, kMarqueePlayer, message, argptr);
    va_end(argptr);
}

Logger &Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::vd(const char *message, va_list argptr) {
    __android_log_print(ANDROID_LOG_DEBUG, kMarqueePlayer, message, argptr);
}
