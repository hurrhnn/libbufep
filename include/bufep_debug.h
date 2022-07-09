#ifndef LIBBUFEP_BUFEP_DEBUG_H
#define LIBBUFEP_BUFEP_DEBUG_H

#include "bufep_config.h"
#include "bufep_logger.h"

#ifdef BUFEP_MS_WINDOWS
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdbool.h>
#endif

enum bufep_debug_colors {
    RED = 0,
    GRN,
    YEL,
    BLU,
    MAG,
    CYN,
    WHT
};

#define BUFEP_DEBUG_COLOR(ENUM) \
    (((ENUM) == RED) ? STR_RED :   \
     ((ENUM) == GRN) ? STR_GRN :   \
     ((ENUM) == YEL) ? STR_YEL :   \
     ((ENUM) == BLU) ? STR_BLU :   \
     ((ENUM) == MAG) ? STR_MAG :   \
     ((ENUM) == CYN) ? STR_CYN :   \
     ((ENUM) == WHT) ? STR_WHT : "" )

#if BUFEP_ENABLE_DEBUG
#define BUFEP_DEBUG(CLR, fmt, ...) \
    BUFEP_LOGGER_PRINTF("%s" fmt "%s", (BUFEP_DEBUG_COLOR(CLR)), ##__VA_ARGS__, STR_RST)
#define BUFEP_DEBUG_MORE(CLR, fmt, ...) \
    BUFEP_LOGGER_PRINTF("%s[%s:%02d]: %s() - " fmt "%s", (BUFEP_DEBUG_COLOR(CLR)), __FILENAME__, __LINE__, __func__, ##__VA_ARGS__, STR_RST)
#else
#define BUFEP_DEBUG(CLR, fmt, ...) do {} while (0)
#define BUFEP_DEBUG_MORE(CLR, fmt, ...) do {} while (0)
#endif

#endif //LIBBUFEP_BUFEP_DEBUG_H
