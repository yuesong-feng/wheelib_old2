/*-------------------------------------------------------------------------
 *
 * str.c
 *	  string for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/str.c
 *
 *
 * NOTES
 *	  string for wheelib
 *
 *-------------------------------------------------------------------------
 */
#include "str.h"

#include <stdlib.h>
#include <string.h>

void str_init(str_t *str) { str->len = 0; }

void str_destroy(str_t *str) {
  str_node_t *node = NULL;
  LIST_FOR_EACH(str->list, node, link) { free(node); }
}

void str_append(str_t *str, const char *content, size len) {
  const char *p = content;
  if (str->len < STR_NODESZ) {  // buf is not full
    size buf_remain = STR_NODESZ - str->len;
    if (buf_remain >= len) {  // buf can hold all content
      memcpy(str->buf + str->len, p, len);
      str->len += len;
      return;
    }
    // buf is not enough, need to malloc str node
    memcpy(str->buf + str->len, p, buf_remain);
    p += buf_remain;
    len -= buf_remain;
    str->len += buf_remain;
  }
  // buf is full
  str_node_t *last_node = LIST_GET_TAIL(str->list);  // get last node
  if (last_node != NULL && last_node->len < STR_NODESZ) {
    size last_remain = STR_NODESZ - last_node->len;
    if (last_remain >= len) {  // last node can hold all content
      memcpy(last_node->buf + last_node->len, p, len);
      last_node->len += len;
      str->len += len;
      return;
    }
    // last buf is not enough, need to malloc str node
    memcpy(last_node->buf + last_node->len, p, last_remain);
    p += last_remain;
    len -= last_remain;
    str->len += last_remain;
  }
  // malloc new node
  str_node_t *node = NULL;
  if (len > STR_NODESZ) {  // a new node to store all the remain content
    node = malloc(sizeof(str_node_t) + len - STR_NODESZ);
    node->len = len;
    memcpy(node->buf, p, STR_NODESZ);
    memcpy(node->extend, p + STR_NODESZ, len - STR_NODESZ);
  } else {
    node = malloc(sizeof(str_node_t));
    node->len = len;
    memcpy(node->buf, p, len);
  }
  LIST_ADD_TAIL(str->list, node, link);
  str->len += len;
}

void str_dump(str_t *str, char *dest) {
  char *p = dest;
  size first_dump = str->len < STR_NODESZ ? str->len : STR_NODESZ;
  str_node_t *node = NULL;
  strncpy(p, str->buf, first_dump);
  p += first_dump;
  LIST_FOR_EACH(str->list, node, link) {
    if (node->len <= STR_NODESZ) {
      strncpy(p, node->buf, node->len);
    } else {
      strncpy(p, node->buf, STR_NODESZ);
      p += STR_NODESZ;
      strncpy(p, node->extend, node->len - STR_NODESZ);
    }
  }
}