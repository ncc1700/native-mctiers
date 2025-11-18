#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED






#ifdef _WIN32

#define _AMD64_
#include <minwindef.h>
#elif __linux__
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT*              PFLOAT;
typedef BOOL*               PBOOL;
typedef int*                PINT;
typedef long*                LONG;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef void                VOID;

typedef unsigned long       UINT64;
typedef unsigned int        UINT32;

typedef unsigned char       UINT8;
typedef char                CHAR;
typedef char*               PCHAR;
typedef voidClass           *PVOID;
#endif






















#endif