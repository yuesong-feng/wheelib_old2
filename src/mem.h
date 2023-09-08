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

#include "hardware.h"
#include "type.h"
#include "wl_assert.h"

static inline void write1b(void *dest, uint8 v) { *(uint8 *)dest = v; }

static inline void write2b(void *dest, uint16 v)
{
#if defined(WL_LITTLE_ENDIAN)
    *(uint16 *)dest = v;
#elif defined(WL_BIG_ENDIAN)
    write1b(dest, (uint8)(v & 0xff));
    write1b((uint8 *)dest + 1, (uint8)((v >> 8) & 0xff));
#else
    wl_assert(false);
#endif
}

static inline void write4b(void *dest, uint32 v)
{
#if defined(WL_LITTLE_ENDIAN)
    *(uint32 *)dest = v;
#elif defined(WL_BIG_ENDIAN)
    write2b(dest, (uint16)(v & 0xffff));
    write2b((uint8 *)dest + 2, (uint16)((v >> 16) & 0xffff));
#else
    wl_assert(false);
#endif
}

static inline void write8b(void *dest, uint64 v)
{
#if defined(WL_LITTLE_ENDIAN)
    *(uint64 *)dest = v;
#elif defined(WL_BIG_ENDIAN)
    write4b(dest, (uint32)(v & 0xffffffff));
    write4b((uint8 *)dest + 4, (uint32)((v >> 32) & 0xffffffff));
#else
    wl_assert(false);
#endif
}

static inline uint8 read1b(void *src) { return *(uint8 *)src; }

static inline uint16 read2b(void *src)
{
#if defined(WL_LITTLE_ENDIAN)
    return *(uint16 *)src;
#elif defined(WL_BIG_ENDIAN)
    uint16 n1, n2;
    uint16 res;
    n1 = read1b(src);
    n2 = read1b((uint8 *)src + 1);
    res = n2 << 8;
    res += n1;
    return res;
#else
    wl_assert(false);
#endif
}

static inline uint32 read4b(void *src)
{
#if defined(WL_LITTLE_ENDIAN)
    return *(uint32 *)src;
#elif defined(WL_BIG_ENDIAN)
    uint32 n1, n2;
    uint32 res;
    n1 = read2b(src);
    n2 = read2b((uint8 *)src + 2);
    res = n2 << 16;
    res += n1;
    return res;
#else
    wl_assert(false);
#endif
}

static inline uint64 read8b(void *src)
{
#if defined(WL_LITTLE_ENDIAN)
    return *(uint64 *)src;
#elif defined(WL_BIG_ENDIAN)
    uint64 n1, n2;
    uint64 res;
    n1 = read4b(src);
    n2 = read4b((uint8 *)src + 4);
    res = n2 << 32;
    res += n1;
    return res;
#else
    wl_assert(false);
#endif
}

#endif
