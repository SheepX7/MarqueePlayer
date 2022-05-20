#ifndef MARQUEEPLAYER_MARQUEE_LOG_H
#define MARQUEEPLAYER_MARQUEE_LOG_H


#include <cstdio>

class Logger {
public:
    Logger();
    static void e(const char *message, ...) __attribute__((format (printf, 1, 2)));
    static void w(const char *message, ...) __attribute__((format (printf, 1, 2)));
    static void d(const char *message, ...) __attribute__((format (printf, 1, 2)));

    static void vd(const char *message, va_list a);

    static Logger &getInstance();
};

extern bool LOGS_ENABLED;

#define DEBUG_E Logger::getInstance().e
#define DEBUG_W Logger::getInstance().w
#define DEBUG_D Logger::getInstance().d
#define DEBUG_VD Logger::getInstance().vd
#define LOGS_ENABLED false


#endif //MARQUEEPLAYER_MARQUEE_LOG_H
