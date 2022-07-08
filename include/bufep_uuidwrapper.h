#ifndef LIBBUFEP_BUFEP_UUIDWRAPPER_H
#define LIBBUFEP_BUFEP_UUIDWRAPPER_H

#if defined(HAVE_UUID_H)
#include <uuid.h>
#elif defined(HAVE_UUID_UUID_H)
#include <uuid/uuid.h>
#endif

#ifdef MS_WINDOWS
#include <rpc.h>
#endif

#endif //LIBBUFEP_BUFEP_UUIDWRAPPER_H
