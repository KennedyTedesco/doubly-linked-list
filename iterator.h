#ifndef DL_ITERATOR_H
#define DL_ITERATOR_H

#include "list.h"

typedef enum { LIST_HEAD, LIST_TAIL } list_direction_t;

typedef struct {
  node_t *next;
  list_direction_t direction;
} iterator_t;

node_t *iterator_next(iterator_t *self);
iterator_t *iterator_from_list(list_t *list, list_direction_t direction);
iterator_t *iterator_from_node(node_t *node, list_direction_t direction);

void iterator_destroy(iterator_t *self);

#endif
