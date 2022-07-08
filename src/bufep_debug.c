#include "bufep_debug.h"

#ifdef BUFEP_MS_WINDOWS
static bool bufep_is_console_initiated = false;

void bufep_debug_init_console() {
    if (!bufep_is_console_initiated) {
        bufep_is_console_initiated = true;

        DWORD outMode = 0;
        HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (stdoutHandle == INVALID_HANDLE_VALUE)
            exit(GetLastError());

        if (!GetConsoleMode(stdoutHandle, &outMode))
            exit(GetLastError());

        // Enable ANSI escape codes
        outMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING

        if (!SetConsoleMode(stdoutHandle, outMode))
            exit(GetLastError());
    }
}
#else
void bufep_debug_init_console() { }
#endif
