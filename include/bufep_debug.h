#ifndef LIBBUFEP_BUFEP_DEBUG_H
#define LIBBUFEP_BUFEP_DEBUG_H

#include "bufep_config.h"

enum bufep_debug_colors {
    RED = 0,
    GRN,
    YEL,
    BLU,
    MAG,
    CYN,
    WHT
};

#define STR_RST   "\x1B[0m"
#define STR_RED   "\x1B[31m"
#define STR_GRN   "\x1B[32m"
#define STR_YEL   "\x1B[33m"
#define STR_BLU   "\x1B[34m"
#define STR_MAG   "\x1B[35m"
#define STR_CYN   "\x1B[36m"
#define STR_WHT   "\x1B[37m"

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
    printf("%s" fmt "%s", (BUFEP_DEBUG_COLOR(CLR)), ##__VA_ARGS__, STR_RST)
#define BUFEP_DEBUG_MORE(CLR, fmt, ...) \
    printf("%s[%s:%02d]: %s() - " fmt "%s", (BUFEP_DEBUG_COLOR(CLR)), __FILENAME__, __LINE__, __func__, ##__VA_ARGS__, STR_RST)
#else
#define BUFEP_DEBUG(CLR, fmt, ...) do {} while (0)
#define BUFEP_DEBUG_MORE(CLR, fmt, ...) do {} while (0)
#endif

#endif //LIBBUFEP_BUFEP_DEBUG_H
