#include "bufep_debug.h"

int bufep_debug(const char * str, ...) {
    return printf("%s", str);
}

int main() {
    printf(RED "red\n"     RST);
    printf(GRN "green\n"   RST);
    printf(YEL "yellow\n"  RST);
    printf(BLU "blue\n"    RST);
    printf(MAG "magenta\n" RST);
    printf(CYN "cyan\n"    RST);
    printf(WHT "white\n"   RST);

    return 0;
}
