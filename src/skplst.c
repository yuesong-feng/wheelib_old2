// #include "skplst.h"

// #include <stddef.h>
// #include <assert.h>

// static int skplst_random_height() {
//   // increase height with probability 1 in k
//   int k = 4;
//   int height = 1;
//   while (height < SKPLST_MAX_HEIGHT && rand_one_in_k(k)) {
//     height++;
//   }
//   assert(height <= SKPLST_MAX_HEIGHT);
//   return height;
// }

// static skplst_node_t *skplst_node_create(void *key, int height) {
//   skplst_node_t *node = malloc(sizeof(skplst_node_t) + sizeof(skplst_node_t *) * (height - 1));
//   node->key = key;
//   return node;
// }
// static void skplst_node_free(skplst_node_t *node) {
//   free(node);
// }

// void skplst_init(skplst_t *sl, comparator cmp) {
//   sl->head = skplst_node_create(NULL, SKPLST_MAX_HEIGHT);
//   sl->max_height = 1;
//   sl->cmp = cmp;
//   for (int i = 0; i < SKPLST_MAX_HEIGHT; ++i) {
//     sl->head->next[i] = NULL;
//   }
// }
// void skplst_destroy(skplst_t *sl) {}

// static skplst_node_t *skplst_find_greate_or_equal(skplst_t *sl, void *key, skplst_node_t **prev) {
//   skplst_node_t *node = sl->head;
//   int level = sl->max_height - 1;
//   while (true) {
//     skplst_node_t *next = node->next[level];
//     if (next != NULL && sl->cmp(next->key, key) < 0) {
//       node = next;  // Keep searching in this list
//     } else {
//       if (prev != NULL) prev[level] = node;
//       if (level == 0)
//         return next;
//       else
//         level--;  // switch to next list
//     }
//   }
// }
// static skplst_node_t *skplst_find_less_than(skplst_t *sl, void *key) {
//   skplst_node_t *node = sl->head;
//   int level = sl->max_height - 1;
//   while (true) {
//     assert(node == sl->head || sl->cmp(node->key, key) < 0);
//     skplst_node_t *next = node->next[level];
//     if (next == NULL || sl->cmp(next->key, key) >= 0) {
//       if (level == 0)
//         return node;
//       else
//         level--;  //switch to next list
//     } else
//       node = next;
//   }
// }
// static skplst_node_t *skplst_find_last(skplst_t *sl) {
//   skplst_node_t *node = sl->head;
//   int level = sl->max_height - 1;
//   while (true) {
//     skplst_node_t *next = node->next;
//     if (next == NULL) {
//       if (level == 0)
//         return node;
//       else
//         level--;  // switch to next list
//     } else
//       node = next;
//   }
// }

// bool skplst_contains(skplst_t *sl, void *key) {
//   skplst_node_t *node = skplst_find_ge(sl, key);
//   if (node != NULL && sl->cmp(key, node->key) == 0) return true;
//   return false;
// }

// void skplst_insert(skplst_t *sl, void *key) {
//   skplst_node_t* prev[SKPLST_MAX_HEIGHT];
//   skplst_node_t* node = skplst_find_greate_or_equal(sl, key, prev);
//   assert (node == NULL || sl->cmp(node->key, key) != 0);  // do not support duplicate insertion
  
//   int height = skplst_random_height();
//   if (height > sl->max_height) {
//     for (int i = sl->max_height; i < height; ++i) {
//       prev[i] = sl->head;
//     }
//     sl->max_height = height;
//   }

//   node = skplst_node_create(key, height);
//   for (int i = 0; i < height; ++i) {
//     node->next[i] = prev[i]->next[i];
//     prev[i]->next[i] = node;
//   }
// }

