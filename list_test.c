/*-------------------------------------------------------------------------
 *
 * main.c
 *	  playground for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  main.c
 *
 *
 * NOTES
 *	  This files wires up the lower level heapam.c et al routines with the
 *	  tableam abstraction.
 *
 *-------------------------------------------------------------------------
 */
#include "list.h"
#include "log.h"

struct info_node {
  int id;
  LIST_NODE(struct info_node) link;
};

struct info {
  LIST(struct info_node) list;
};

int main(int argc, char const *argv[]) {
  struct info i = {LIST_INITIALIZER};

  struct info_node n1 = {123, LIST_NODE_INITIALIZER};
  LIST_ADD_TAIL(i.list, &n1, link);

  struct info_node n2 = {234, LIST_NODE_INITIALIZER};
  LIST_ADD_TAIL(i.list, &n2, link);

  LOG_INFO("%d", LIST_GET_LEN(i.list));

  struct info_node *p = NULL;
  LIST_FOR_EACH(i.list, p, link) { LOG_INFO("%d", p->id); }
  return 0;
}
