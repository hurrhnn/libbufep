#ifndef LIBBUFEP_BUFEP_LOGGER_H
#define LIBBUFEP_BUFEP_LOGGER_H

#include "bufep_config.h"

#ifdef BUFEP_MS_WINDOWS
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdbool.h>
#endif

#define STR_RST   "\x1B[0m"
#define STR_RED   "\x1B[31m"
#define STR_GRN   "\x1B[32m"
#define STR_YEL   "\x1B[33m"
#define STR_BLU   "\x1B[34m"
#define STR_MAG   "\x1B[35m"
#define STR_CYN   "\x1B[36m"
#define STR_WHT   "\x1B[37m"

#define BUFEP_LOGGER_PRINTF(fmt, ...) \
do {                                  \
    bufep_logger_init_console();      \
    printf(fmt, ##__VA_ARGS__);       \
} while (0)

#define BUFEP_INFO(fmt, ...) \
    BUFEP_LOGGER_PRINTF(##__VA_ARGS__)
#define BUFEP_WARN(fmt, ...) \
    BUFEP_LOGGER_PRINTF("%s" fmt "%s", STR_YEL, ##__VA_ARGS__, STR_RST)
#define BUFEP_ERROR(fmt, ...) \
    BUFEP_LOGGER_PRINTF("%s" fmt "%s", STR_RED, ##__VA_ARGS__, STR_RST)

void bufep_logger_init_console(void);

#endif //LIBBUFEP_BUFEP_LOGGER_H
