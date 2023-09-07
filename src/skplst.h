/*-------------------------------------------------------------------------
 *
 * skplst.h
 *	  skiplist for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/skplst.h
 *
 *
 * NOTES
 *	  skiplist from leveldb
 * next[n]  ___                                          ___
 * next[4] |___|-----------------------___ ------------>|___|------------>NULL
 * next[3] |___|--------------------->|___|-----___---->|___|------------>NULL
 * next[2] |___|-----___------------->|___|--->|___|--->|___|------------>NULL
 * next[1] |___|--->|___|-----___---->|___|--->|___|--->|___|-----___---->NULL
 * next[0] |___|--->|___|--->|___|--->|___|--->|___|--->|___|--->|___|--->NULL
 * key     |head|    | 4 |    | 6 |    | 9 |    |13 |    |14 |    |16 |
 *
 *-------------------------------------------------------------------------
 */
#ifndef SKPLST_H
#define SKPLST_H

#include "cmp.h"

#define SKPLST_MAX_HEIGHT 12

typedef struct skplst_node_struct {
  void *key;
  skplst_node_t *next[1];
} skplst_node_t;

typedef struct skplst_struct {
  skplst_node_t *head;
  int max_height;
  comparator cmp;
} skplst_t;

void skplst_init(skplst_t *sl, comparator cmp);
void skplst_destroy(skplst_t *sl);

bool skplst_contains(skplst_t *sl, void *key);

void skplst_insert(skplst_t* sl, void *key);

#endif
