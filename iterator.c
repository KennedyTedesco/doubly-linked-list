#include <stdlib.h>

#include "iterator.h"

iterator_t *iterator_from_list(list_t *list, list_direction_t direction) {
  node_t *node = direction == LIST_HEAD ? list->head : list->tail;
  return iterator_from_node(node, direction);
}

iterator_t *iterator_from_node(node_t *node, list_direction_t direction) {
  iterator_t *iterator = malloc(sizeof(iterator_t));
  if (iterator == NULL) {
	return NULL;
  }
  iterator->next = node;
  iterator->direction = direction;
  return iterator;
}

node_t *iterator_next(iterator_t *iterator) {
  if (iterator->direction == LIST_HEAD) {
	return iterator->next = iterator->next->next;
  }
  return iterator->next = iterator->next->prev;
}

void iterator_destroy(iterator_t *iterator) {
  free(iterator);
}
