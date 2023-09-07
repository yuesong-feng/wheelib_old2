/*-------------------------------------------------------------------------
 *
 * mem.h
 *	  mem operations for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/mem.h
 *
 *
 * NOTES
 *	  mem operations for wheelib
 *
 *-------------------------------------------------------------------------
 */
#ifndef MEM_H
#define MEM_H

#include "type.h"

static inline void write1b(void *dest, uint8 v) { *(uint8 *)dest = v; }

static inline void write2b(void *dest, uint16 v)
{
#ifdef __LITTLE_ENDIAN__
    *(uint16 *)dest = v;
#else
    write1b(dest, (uint8)(v & 0xff));
    write1b((uint8 *)dest + 1, (uint8)((v >> 8) & 0xff));
#endif
}

static inline void write4b(void *dest, uint32 v)
{
#ifdef __LITTLE_ENDIAN__
    *(uint32 *)dest = v;
#else
    write2b(dest, (uint16)(v & 0xffff));
    write2b((uint8 *)dest + 2, (uint16)((v >> 16) & 0xffff));
#endif
}

static inline void write8b(void *dest, uint64 v)
{
#ifdef __LITTLE_ENDIAN__
    *(uint64 *)dest = v;
#else
    write4b(dest, (uint32)(v & 0xffffffff));
    write4b((uint8 *)dest + 4, (uint32)((v >> 32) & 0xffffffff));
#endif
}

static inline uint8 read1b(void *src) { return *(uint8 *)src; }

static inline uint16 read2b(void *src)
{
#ifdef __LITTLE_ENDIAN__
    return *(uint16 *)src;
#else
    uint16 n1, n2;
    uint16 res;
    n1 = read1b(src);
    n2 = read1b((uint8 *)src + 1);
    res = n2 << 8;
    res += n1;
    return res;
#endif
}

static inline uint32 read4b(void *src)
{
#ifdef __LITTLE_ENDIAN__
    return *(uint32 *)src;
#else
    uint32 n1, n2;
    uint32 res;
    n1 = read2b(src);
    n2 = read2b((uint8 *)src + 2);
    res = n2 << 16;
    res += n1;
    return res;
#endif
}

static inline uint64 read8b(void *src)
{
#ifdef __LITTLE_ENDIAN__
    return *(uint64 *)src;
#else
    uint64 n1, n2;
    uint64 res;
    n1 = read4b(src);
    n2 = read4b((uint8 *)src + 4);
    res = n2 << 32;
    res += n1;
    return res;
#endif
}

#endif
