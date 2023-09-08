/*-------------------------------------------------------------------------
 *
 * type.h
 *	  type definitions for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/type.h
 *
 *
 * NOTES
 *	  type definitions for wheelib
 *
 *-------------------------------------------------------------------------
 */
#ifndef TYPE_H
#define TYPE_H
#include "hardware.h"

#ifdef NULL
#undef NULL
#endif

#define NULL ((void *)0)

typedef unsigned char byte;

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef float float32;
typedef double float64;

#if defined(WL_64)
typedef unsigned long long uintptr;
typedef unsigned long long size;
#elif defined(WL_32)
typedef unsigned int uintptr;
typedef unsigned int size;
#endif

#ifdef bool
#undef bool
#endif

typedef unsigned char bool;
#define true 1
#define false 0

#endif
