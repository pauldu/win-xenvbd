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

#ifndef _XENBUS_EVTCHN_INTERFACE_H
#define _XENBUS_EVTCHN_INTERFACE_H

#ifndef _WINDLL

typedef enum _XENBUS_EVTCHN_TYPE {
    XENBUS_EVTCHN_TYPE_INVALID = 0,
    XENBUS_EVTCHN_TYPE_FIXED,
    XENBUS_EVTCHN_TYPE_UNBOUND,
    XENBUS_EVTCHN_TYPE_INTER_DOMAIN,
    XENBUS_EVTCHN_TYPE_VIRQ
} XENBUS_EVTCHN_TYPE, *PXENBUS_EVTCHN_TYPE;

typedef struct _XENBUS_EVTCHN_DESCRIPTOR XENBUS_EVTCHN_DESCRIPTOR, *PXENBUS_EVTCHN_DESCRIPTOR;

typedef NTSTATUS
(*XENBUS_EVTCHN_ACQUIRE)(
    IN  PINTERFACE  Interface
    );

typedef VOID
(*XENBUS_EVTCHN_RELEASE)(
    IN  PINTERFACE  Interface
    );

typedef PXENBUS_EVTCHN_DESCRIPTOR
(*XENBUS_EVTCHN_OPEN)(
    IN  PINTERFACE          Interface,
    IN  XENBUS_EVTCHN_TYPE  Type,
    IN  PKSERVICE_ROUTINE   Function,
    IN  PVOID               Argument OPTIONAL,
    ...
    );

typedef BOOLEAN
(*XENBUS_EVTCHN_UNMASK)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_EVTCHN_DESCRIPTOR   Descriptor,
    IN  BOOLEAN                     Locked
    );

typedef VOID
(*XENBUS_EVTCHN_SEND)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_EVTCHN_DESCRIPTOR   Descriptor
    );

typedef VOID
(*XENBUS_EVTCHN_TRIGGER)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_EVTCHN_DESCRIPTOR   Descriptor
    );

typedef ULONG
(*XENBUS_EVTCHN_GET_PORT)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_EVTCHN_DESCRIPTOR   Descriptor
    );

typedef VOID
(*XENBUS_EVTCHN_CLOSE)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_EVTCHN_DESCRIPTOR   Descriptor
    );

typedef BOOLEAN
(*XENBUS_EVTCHN_INTERRUPT)(
    IN  PINTERFACE                  Interface
    );

// {BE2440AC-1098-4150-AF4D-452FADCEF923}
DEFINE_GUID(GUID_XENBUS_EVTCHN_INTERFACE, 
0xbe2440ac, 0x1098, 0x4150, 0xaf, 0x4d, 0x45, 0x2f, 0xad, 0xce, 0xf9, 0x23);

struct _XENBUS_EVTCHN_INTERFACE_V1 {
    INTERFACE               Interface;
    XENBUS_EVTCHN_ACQUIRE   EvtchnAcquire;
    XENBUS_EVTCHN_RELEASE   EvtchnRelease;
    XENBUS_EVTCHN_OPEN      EvtchnOpen;
    XENBUS_EVTCHN_UNMASK    EvtchnUnmask;
    XENBUS_EVTCHN_SEND      EvtchnSend;
    XENBUS_EVTCHN_SEND      EvtchnTrigger;
    XENBUS_EVTCHN_GET_PORT  EvtchnGetPort;
    XENBUS_EVTCHN_INTERRUPT EvtchnInterrupt;
    XENBUS_EVTCHN_CLOSE     EvtchnClose;
};

typedef struct _XENBUS_EVTCHN_INTERFACE_V1 XENBUS_EVTCHN_INTERFACE, *PXENBUS_EVTCHN_INTERFACE;

#define XENBUS_EVTCHN(_Method, _Interface, ...)    \
    (_Interface)->Evtchn ## _Method((PINTERFACE)(_Interface), __VA_ARGS__)

#endif  // _WINDLL

#define XENBUS_EVTCHN_INTERFACE_VERSION_MIN 1
#define XENBUS_EVTCHN_INTERFACE_VERSION_MAX 1

#endif  // _XENBUS_EVTCHN_INTERFACE_H

