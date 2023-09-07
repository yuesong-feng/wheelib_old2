/*-------------------------------------------------------------------------
 *
 * debug.c
 *	  debug tools for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/debug.c
 *
 *
 * NOTES
 *	  debug tools for wheelib
 *
 *-------------------------------------------------------------------------
 */
#include "debug.h"
#include <stdio.h>

void print_mem(void* src, int len) {
  unsigned char* p = src;
  int i = 0;
  printf("          00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  Decoded Text\n");
  for (i = 0; i < len; ++i) {
    if (i % 16 == 0) {
      printf("%08x  ", i);
    }
    printf("%02x ", *(p + i));
    if ((i + 1) % 16 == 0) {
      for (int j = 0; j < 16; ++j) {
        printf(" %c", (*(p + i - 15 + j) >= 0x20 && *(p + i - 15 + j) <= 0x7e) ? *(p + i - 15 + j) : '.');
      }
      printf("\n");
    }
  }
  for (int j = i; j % 16 != 0; ++j) {
    printf("   ");
  }
  for (int j = 0; j < i % 16; ++j) {
    printf(" %c", (*(p + i - (i % 16) + j) >= 0x20 && *(p + i - (i % 16) + j) <= 0x7e) ? *(p + i - (i % 16) + j) : '.');
    if (j + 1 == i % 16)
      printf("\n");
  }
}
