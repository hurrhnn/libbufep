#include "bufep_pmtud.h"
#include "bufep_debug.h"
#include "bufep_private.h"

int bufep_pmtud(bufep_socket_info_t *server_info) {
    struct sockaddr_in server_addr = *server_info->sockaddr_in;

    char buffer[MAXIMUM_MTU] = "";
    int mtu_low_bound, mtu_current, mtu_high_bound, mtu_best;
    ssize_t current_tries;
    socklen_t from_size = sizeof(struct sockaddr_in);

    mtu_best = BUFEP_FAILURE;
    mtu_low_bound = MINIMUM_MTU;
    mtu_high_bound = MAXIMUM_MTU;

    current_tries = PMTUD_MAX_TRIES;
    while (mtu_low_bound <= mtu_high_bound)
    {
        mtu_current = (mtu_low_bound + mtu_high_bound) / 2;
        if (current_tries == PMTUD_MAX_TRIES)
            printf("Testing MTU size %d bytes...", mtu_current);

        if (sendto(server_info->sock_fd, buffer, mtu_current - IPV4_HEADER_SIZE - UDP_HEADER_SIZE, 0,
                   (struct sockaddr *) &server_addr, *server_info->socklen) == -1) {
            if (
#ifdef BUFEP_MS_WINDOWS
                WSAGetLastError() == WSAEMSGSIZE
#else
                errno == EMSGSIZE
#endif
                ) {
                printf(" packet too big for local interface.\n");
                mtu_high_bound = mtu_current - 1;
                continue;
            }
#ifdef BUFEP_MS_WINDOWS
            wchar_t* wError = NULL;
            FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, WSAGetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPWSTR)&wError, 0, NULL);
            BUFEP_ERROR(" %S\n", wError);
            LocalFree(wError);
#else
            perror("Error in sendto()");
#endif
            return BUFEP_FAILURE;
        }

        if (recvfrom(server_info->sock_fd, buffer, MAXIMUM_MTU, 0, (struct sockaddr *) &server_addr, &from_size) < 0) {
            if (
#ifdef BUFEP_MS_WINDOWS
                WSAGetLastError() == WSAEWOULDBLOCK
#else
                errno == EAGAIN || errno == EWOULDBLOCK
#endif
                )
            {
                if (--current_tries == 0)
                {
                    printf(" no response, invalid MTU size.\n");
                    current_tries = PMTUD_MAX_TRIES;
                    mtu_high_bound = mtu_current - 1;
                }
                continue;
            }
#ifdef BUFEP_MS_WINDOWS
            printf("%d", WSAGetLastError());
            wchar_t* wError = NULL;
            FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, WSAGetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPWSTR)&wError, 0, NULL);
            BUFEP_ERROR(" %S\n", wError);
            LocalFree(wError);
#else
            perror("Error in sendto()");
#endif
            return BUFEP_FAILURE;
        }
        printf(" valid.\n");

        current_tries = PMTUD_MAX_TRIES;
        mtu_low_bound = mtu_current + 1;

        if (mtu_current > mtu_best)
            mtu_best = mtu_current;
    }
    return mtu_best;
}
