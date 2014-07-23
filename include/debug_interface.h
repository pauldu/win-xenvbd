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

#ifndef _XENBUS_DEBUG_INTERFACE_H
#define _XENBUS_DEBUG_INTERFACE_H

#ifndef _WINDLL

typedef struct _XENBUS_DEBUG_CALLBACK   XENBUS_DEBUG_CALLBACK, *PXENBUS_DEBUG_CALLBACK;

typedef NTSTATUS
(*XENBUS_DEBUG_ACQUIRE)(
    IN  PINTERFACE  Interface
    );

typedef VOID
(*XENBUS_DEBUG_RELEASE)(
    IN  PINTERFACE  Interface
    );

typedef NTSTATUS
(*XENBUS_DEBUG_REGISTER)(
    IN  PINTERFACE              Interface,
    IN  const CHAR              *Prefix,
    IN  VOID                    (*Function)(PVOID, BOOLEAN),
    IN  PVOID                   Argument OPTIONAL,
    OUT PXENBUS_DEBUG_CALLBACK  *Callback
    );

typedef VOID
(*XENBUS_DEBUG_PRINTF)(
    IN  PINTERFACE              Interface,
    IN  PXENBUS_DEBUG_CALLBACK  Callback,
    IN  const CHAR              *Format,
    ...
    );

typedef VOID
(*XENBUS_DEBUG_DEREGISTER)(
    IN  PINTERFACE              Interface,
    IN  PXENBUS_DEBUG_CALLBACK  Callback
    );

typedef VOID
(*XENBUS_DEBUG_TRIGGER)(
    IN  PINTERFACE              Interface
    );

// {0DF600AE-6B20-4227-BF94-03DA9A26A114}
DEFINE_GUID(GUID_XENBUS_DEBUG_INTERFACE, 
0xdf600ae, 0x6b20, 0x4227, 0xbf, 0x94, 0x3, 0xda, 0x9a, 0x26, 0xa1, 0x14);

struct _XENBUS_DEBUG_INTERFACE_V1 {
    INTERFACE               Interface;
    XENBUS_DEBUG_ACQUIRE    DebugAcquire;
    XENBUS_DEBUG_RELEASE    DebugRelease;
    XENBUS_DEBUG_REGISTER   DebugRegister;
    XENBUS_DEBUG_PRINTF     DebugPrintf;
    XENBUS_DEBUG_TRIGGER    DebugTrigger;
    XENBUS_DEBUG_DEREGISTER DebugDeregister;
};

typedef struct _XENBUS_DEBUG_INTERFACE_V1 XENBUS_DEBUG_INTERFACE, *PXENBUS_DEBUG_INTERFACE;

#define XENBUS_DEBUG(_Method, _Interface, ...)    \
    (_Interface)->Debug ## _Method((PINTERFACE)(_Interface), __VA_ARGS__)

#endif  // _WINDLL

#define XENBUS_DEBUG_INTERFACE_VERSION_MIN  1
#define XENBUS_DEBUG_INTERFACE_VERSION_MAX  1

#endif  // _XENBUS_DEBUG_INTERFACE_H

