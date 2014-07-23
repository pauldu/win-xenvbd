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

#ifndef _XENFILT_EMULATED_INTERFACE_H
#define _XENFILT_EMULATED_INTERFACE_H

#ifndef _WINDLL

typedef enum _XENFILT_EMULATED_OBJECT_TYPE {
    XENFILT_EMULATED_OBJECT_TYPE_INVALID = 0,
    XENFILT_EMULATED_OBJECT_TYPE_DEVICE,
    XENFILT_EMULATED_OBJECT_TYPE_DISK
} XENFILT_EMULATED_OBJECT_TYPE, *PXENFILT_EMULATED_OBJECT_TYPE;

typedef struct _XENFILT_EMULATED_OBJECT XENFILT_EMULATED_OBJECT, *PXENFILT_EMULATED_OBJECT;

typedef NTSTATUS
(*XENFILT_EMULATED_ACQUIRE)(
    IN  PINTERFACE  Interface
    );

typedef VOID
(*XENFILT_EMULATED_RELEASE)(
    IN  PINTERFACE  Interface
    );

typedef BOOLEAN
(*XENFILT_EMULATED_IS_DEVICE_PRESENT)(
    IN  PVOID   Context,
    IN  PCHAR   DeviceID,
    IN  PCHAR   InstanceID
    );

typedef BOOLEAN
(*XENFILT_EMULATED_IS_DISK_PRESENT)(
    IN  PVOID   Context,
    IN  ULONG   Controller,
    IN  ULONG   Target,
    IN  ULONG   Lun
    );

typedef NTSTATUS
(*XENFILT_EMULATED_ADD_OBJECT)(
    IN  PINTERFACE                      Interface,
    IN  XENFILT_EMULATED_OBJECT_TYPE    Type,
    IN  PDEVICE_OBJECT                  DeviceObject,
    OUT PXENFILT_EMULATED_OBJECT        *EmulatedObject
    );

typedef VOID
(*XENFILT_EMULATED_REMOVE_OBJECT)(
    IN  PINTERFACE                  Interface,
    IN  PXENFILT_EMULATED_OBJECT    EmulatedObject
    );

typedef const CHAR *
(*XENFILT_EMULATED_GET_TEXT)(
    IN  PINTERFACE                  Interface,
    IN  PXENFILT_EMULATED_OBJECT    EmulatedObject
    );

// {959027A1-FCCE-4E78-BCF4-637384F499C5}
DEFINE_GUID(GUID_XENFILT_EMULATED_INTERFACE, 
0x959027a1, 0xfcce, 0x4e78, 0xbc, 0xf4, 0x63, 0x73, 0x84, 0xf4, 0x99, 0xc5);

struct _XENFILT_EMULATED_INTERFACE_V1 {
    INTERFACE                           Interface;
    XENFILT_EMULATED_ACQUIRE            EmulatedAcquire;
    XENFILT_EMULATED_RELEASE            EmulatedRelease;
    XENFILT_EMULATED_IS_DEVICE_PRESENT  EmulatedIsDevicePresent;
    XENFILT_EMULATED_IS_DISK_PRESENT    EmulatedIsDiskPresent;
    XENFILT_EMULATED_ADD_OBJECT         EmulatedAddObject;
    XENFILT_EMULATED_REMOVE_OBJECT      EmulatedRemoveObject;
    XENFILT_EMULATED_GET_TEXT           EmulatedGetText;
};

typedef struct _XENFILT_EMULATED_INTERFACE_V1 XENFILT_EMULATED_INTERFACE, *PXENFILT_EMULATED_INTERFACE;

#define XENFILT_EMULATED(_Method, _Interface, ...)    \
    (_Interface)->Emulated ## _Method((PINTERFACE)(_Interface), __VA_ARGS__)

#endif  // _WINDLL

#define XENFILT_EMULATED_INTERFACE_VERSION_MIN  1
#define XENFILT_EMULATED_INTERFACE_VERSION_MAX  1

#endif  // _XENFILT_EMULATED_INTERFACE_H

