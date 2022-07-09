#ifndef LIBBUFEP_BUFEP_UUIDWRAPPER_H
#define LIBBUFEP_BUFEP_UUIDWRAPPER_H

#include "bufep_config.h"

#ifdef BUFEP_LINUX
#include <uuid.h>
#elif defined(BUFEP_MAC_OS_X)
#include <uuid/uuid.h>
#elif defined(MS_WINDOWS)
#include <rpc.h>
#endif

#endif //LIBBUFEP_BUFEP_UUIDWRAPPER_H
