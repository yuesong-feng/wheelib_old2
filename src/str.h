/*-------------------------------------------------------------------------
 *
 * str.h
 *	  string for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/str.h
 *
 *
 * NOTES
 *	  string for wheelib
 *
 *-------------------------------------------------------------------------
 */
#ifndef STR_H
#define STR_H

#include "list.h"

#define STR_NODESZ 1024

typedef struct str_node_struct str_node_t;
struct str_node_struct {
  size len;
  LIST_NODE(str_node_t) link;
  char buf[STR_NODESZ];
  char extend[0];
};

typedef struct str_struct str_t;
struct str_struct {
  size len;
  char buf[STR_NODESZ];
  LIST(str_node_t) list;
};

#define STR_INITIALIZER \
  { 0, {}, LIST_INITIALIZER }

void str_init(str_t *str);
void str_destroy(str_t *str);
void str_append(str_t *str, const char *content, size len);
void str_dump(str_t *str, char *dest);

#endif
