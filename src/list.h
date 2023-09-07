/*-------------------------------------------------------------------------
 *
 * list.h
 *	  list for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/list.h
 *
 *
 * NOTES
 *	  double linked list
 *
 *-------------------------------------------------------------------------
 */
#ifndef LIST_H
#define LIST_H
#include <type.h>

#define LIST(TYPE) \
  struct {         \
    size len;    \
    TYPE* head;    \
    TYPE* tail;    \
  }

#define LIST_NODE(TYPE) \
  struct {              \
    TYPE* prev;         \
    TYPE* next;         \
  }

#define LIST_INITIALIZER \
  { 0, NULL, NULL }

#define LIST_INIT(list) \
  do {                  \
    (list).len = 0;     \
    (list).head = NULL; \
    (list).tail = NULL; \
  } while (0)

#define LIST_NODE_INITIALIZER \
  { NULL, NULL }

#define LIST_NODE_INIT(node) \
  do {                       \
    (node).prev = NULL;      \
    (node).next = NULL;      \
  } while (0)

#define LIST_ADD_TAIL(list, node, link)    \
  do {                                     \
    if ((list).len == 0) {                 \
      ((node)->link).next = NULL;          \
      ((node)->link).prev = NULL;          \
      (list).head = (node);                \
      (list).tail = (node);                \
    } else {                               \
      ((node)->link).prev = (list).tail;   \
      ((node)->link).next = NULL;          \
      (((list).tail)->link).next = (node); \
      (list).tail = (node);                \
    }                                      \
    ((list).len)++;                        \
  } while (0)

#define LIST_ADD_HEAD(list, node, link)    \
  do {                                     \
    if ((list).len == 0) {                 \
      ((node)->link).next = NULL;          \
      ((node)->link).prev = NULL;          \
      (list).head = (node);                \
      (list).tail = (node);                \
    } else {                               \
      ((node)->link).prev = NULL;          \
      ((node)->link).next = (list).head;   \
      (((list).head)->link).prev = (node); \
      (list).head = (node);                \
    }                                      \
    ((list).len)++;                        \
  } while (0)

#define LIST_GET_LEN(list) ((list).len)
#define LIST_GET_HEAD(list) ((list).head)
#define LIST_GET_TAIL(list) ((list).tail)

#define LIST_FOR_EACH(list, node, link) \
  for ((node) = (list).head; (node) != NULL; (node) = ((node)->link).next)

#endif
