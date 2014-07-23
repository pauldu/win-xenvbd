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

#ifndef _XENBUS_GNTTAB_INTERFACE_H
#define _XENBUS_GNTTAB_INTERFACE_H

#ifndef _WINDLL

typedef struct _XENBUS_GNTTAB_CACHE         XENBUS_GNTTAB_CACHE, *PXENBUS_GNTTAB_CACHE;
typedef struct _XENBUS_GNTTAB_DESCRIPTOR    XENBUS_GNTTAB_DESCRIPTOR, *PXENBUS_GNTTAB_DESCRIPTOR;

typedef NTSTATUS
(*XENBUS_GNTTAB_ACQUIRE)(
    IN  PINTERFACE  Interface
    );

typedef VOID
(*XENBUS_GNTTAB_RELEASE)(
    IN  PINTERFACE  Interface
    );

typedef NTSTATUS
(*XENBUS_GNTTAB_CREATE_CACHE)(
    IN  PINTERFACE              Interface,
    IN  const CHAR              *Name,
    IN  ULONG                   Reservation,
    IN  VOID                    (*AcquireLock)(PVOID),
    IN  VOID                    (*ReleaseLock)(PVOID),
    IN  PVOID                   Argument OPTIONAL,
    OUT PXENBUS_GNTTAB_CACHE    *Cache
    );

typedef NTSTATUS
(*XENBUS_GNTTAB_PERMIT_FOREIGN_ACCESS)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_GNTTAB_CACHE        Cache,
    IN  BOOLEAN                     Locked,
    IN  USHORT                      Domain,
    IN  PFN_NUMBER                  Pfn,
    IN  BOOLEAN                     ReadOnly,
    OUT PXENBUS_GNTTAB_DESCRIPTOR   *Descriptor
    );

typedef NTSTATUS
(*XENBUS_GNTTAB_REVOKE_FOREIGN_ACCESS)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_GNTTAB_CACHE        Cache,
    IN  BOOLEAN                     Locked,
    IN  PXENBUS_GNTTAB_DESCRIPTOR   Descriptor
    );

typedef ULONG
(*XENBUS_GNTTAB_GET_REFERENCE)(
    IN  PINTERFACE                  Interface,
    IN  PXENBUS_GNTTAB_DESCRIPTOR   Descriptor
    );

typedef VOID
(*XENBUS_GNTTAB_DESTROY_CACHE)(
    IN  PINTERFACE              Interface,
    IN  PXENBUS_GNTTAB_CACHE    Cache
    );

// {763679C5-E5C2-4A6D-8B88-6BB02EC42D8E}
DEFINE_GUID(GUID_XENBUS_GNTTAB_INTERFACE, 
0x763679c5, 0xe5c2, 0x4a6d, 0x8b, 0x88, 0x6b, 0xb0, 0x2e, 0xc4, 0x2d, 0x8e);

struct _XENBUS_GNTTAB_INTERFACE_V1 {
    INTERFACE                           Interface;
    XENBUS_GNTTAB_ACQUIRE               GnttabAcquire;
    XENBUS_GNTTAB_RELEASE               GnttabRelease;
    XENBUS_GNTTAB_CREATE_CACHE          GnttabCreateCache;
    XENBUS_GNTTAB_PERMIT_FOREIGN_ACCESS GnttabPermitForeignAccess;
    XENBUS_GNTTAB_REVOKE_FOREIGN_ACCESS GnttabRevokeForeignAccess;
    XENBUS_GNTTAB_GET_REFERENCE         GnttabGetReference;
    XENBUS_GNTTAB_DESTROY_CACHE         GnttabDestroyCache;
};

typedef struct _XENBUS_GNTTAB_INTERFACE_V1 XENBUS_GNTTAB_INTERFACE, *PXENBUS_GNTTAB_INTERFACE;

#define XENBUS_GNTTAB(_Method, _Interface, ...)    \
    (_Interface)->Gnttab ## _Method((PINTERFACE)(_Interface), __VA_ARGS__)

#endif  // _WINDLL

#define XENBUS_GNTTAB_INTERFACE_VERSION_MIN 1
#define XENBUS_GNTTAB_INTERFACE_VERSION_MAX 1

#endif  // _XENBUS_GNTTAB_INTERFACE_H

