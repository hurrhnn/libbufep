#include <bufep.h>

int main() {
    BUFEP_DEBUG(RED, "THIS COLOR IS RED.\n");
    BUFEP_DEBUG(GRN, "THIS COLOR IS GREEN.\n");
    BUFEP_DEBUG(YEL, "THIS COLOR IS YELLOW.\n");
    BUFEP_DEBUG_MORE(BLU, "THIS COLOR IS BLUE.\n");
    BUFEP_DEBUG_MORE(MAG, "THIS COLOR IS MAGENTA.\n");
    BUFEP_DEBUG_MORE(CYN, "THIS COLOR IS CYAN.\n");
    BUFEP_DEBUG_MORE(WHT, "THIS COLOR IS WHITE.\n");
}
