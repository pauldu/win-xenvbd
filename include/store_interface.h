/* Copyright (c) Citrix Systems Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, 
 * with or without modification, are permitted provided 
 * that the following conditions are met:
 * 
 * *   Redistributions of source code must retain the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer.
 * *   Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer in the documentation and/or other 
 *     materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 */

#ifndef _XENBUS_STORE_INTERFACE_H
#define _XENBUS_STORE_INTERFACE_H

#ifndef _WINDLL

typedef struct _XENBUS_STORE_TRANSACTION    XENBUS_STORE_TRANSACTION, *PXENBUS_STORE_TRANSACTION;
typedef struct _XENBUS_STORE_WATCH          XENBUS_STORE_WATCH, *PXENBUS_STORE_WATCH;

typedef NTSTATUS
(*XENBUS_STORE_ACQUIRE)(
    IN  PINTERFACE  Interface
    );

typedef VOID
(*XENBUS_STORE_RELEASE)(
    IN  PINTERFACE  Interface
    );

typedef VOID
(*XENBUS_STORE_FREE)(
    IN  PINTERFACE  Interface,
    IN  PCHAR       Buffer
    );

typedef NTSTATUS
(*XENBUS_STORE_READ)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_STORE_TRANSACTION   Transaction OPTIONAL,
    IN  PCHAR                       Prefix OPTIONAL,
    IN  PCHAR                       Node,
    OUT PCHAR                       *Buffer
    );

typedef NTSTATUS
(*XENBUS_STORE_PRINTF)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_STORE_TRANSACTION   Transaction OPTIONAL,
    IN  PCHAR                       Prefix OPTIONAL,
    IN  PCHAR                       Node,
    IN  const CHAR                  *Format,
    ...
    );

typedef NTSTATUS
(*XENBUS_STORE_REMOVE)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_STORE_TRANSACTION   Transaction OPTIONAL,
    IN  PCHAR                       Prefix OPTIONAL,
    IN  PCHAR                       Node
    );

typedef NTSTATUS
(*XENBUS_STORE_DIRECTORY)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_STORE_TRANSACTION   Transaction OPTIONAL,
    IN  PCHAR                       Prefix OPTIONAL,
    IN  PCHAR                       Node,
    OUT PCHAR                       *Buffer
    );

typedef NTSTATUS
(*XENBUS_STORE_TRANSACTION_START)(
    IN  PINTERFACE                  Interface,
    OUT PXENBUS_STORE_TRANSACTION   *Transaction
    );

typedef NTSTATUS
(*XENBUS_STORE_TRANSACTION_END)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_STORE_TRANSACTION   Transaction,
    IN  BOOLEAN                     Commit
    );

typedef NTSTATUS
(*XENBUS_STORE_WATCH_ADD)(
    IN  PINTERFACE          Interface,
    IN  PCHAR               Prefix OPTIONAL,
    IN  PCHAR               Node,
    IN  PKEVENT             Event,
    OUT PXENBUS_STORE_WATCH *Watch
    );

typedef NTSTATUS
(*XENBUS_STORE_WATCH_REMOVE)(
    IN  PINTERFACE          Interface,
    IN  PXENBUS_STORE_WATCH Watch
    );

typedef VOID
(*XENBUS_STORE_POLL)(
    IN  PINTERFACE  Interface
    );

// {86824C3B-D34E-4753-B281-2F1E3AD214D7}
DEFINE_GUID(GUID_XENBUS_STORE_INTERFACE, 
0x86824c3b, 0xd34e, 0x4753, 0xb2, 0x81, 0x2f, 0x1e, 0x3a, 0xd2, 0x14, 0xd7);

struct _XENBUS_STORE_INTERFACE_V1 {
    INTERFACE                       Interface;
    XENBUS_STORE_ACQUIRE            StoreAcquire;
    XENBUS_STORE_RELEASE            StoreRelease;
    XENBUS_STORE_FREE               StoreFree;
    XENBUS_STORE_READ               StoreRead;
    XENBUS_STORE_PRINTF             StorePrintf;
    XENBUS_STORE_REMOVE             StoreRemove;
    XENBUS_STORE_DIRECTORY          StoreDirectory;
    XENBUS_STORE_TRANSACTION_START  StoreTransactionStart;
    XENBUS_STORE_TRANSACTION_END    StoreTransactionEnd;
    XENBUS_STORE_WATCH_ADD          StoreWatchAdd;
    XENBUS_STORE_WATCH_REMOVE       StoreWatchRemove;
    XENBUS_STORE_POLL               StorePoll;
};

typedef struct _XENBUS_STORE_INTERFACE_V1 XENBUS_STORE_INTERFACE, *PXENBUS_STORE_INTERFACE;

#define XENBUS_STORE(_Method, _Interface, ...)    \
    (_Interface)->Store ## _Method((PINTERFACE)(_Interface), __VA_ARGS__)

#endif  // _WINDLL

#define XENBUS_STORE_INTERFACE_VERSION_MIN  1
#define XENBUS_STORE_INTERFACE_VERSION_MAX  1

#endif  // _XENBUS_STORE_INTERFACE_H

