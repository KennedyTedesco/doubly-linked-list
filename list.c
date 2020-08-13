#include <stdlib.h>

#include "list.h"
#include "iterator.h"

list_t *list_create() {
  list_t *list = malloc(sizeof(list_t));

  if (list == 0) {
	return NULL;
  }

  list->len = 0;
  list->head = NULL;
  list->tail = NULL;
  list->match = NULL;

  return list;
}

node_t *node_create(void *data) {
  node_t *node = malloc(sizeof(node_t));

  if (node == 0) {
	return NULL;
  }

  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

node_t *insert_front(list_t *list, void *data) {
  node_t *node = node_create(data);

  if (list->head == NULL) {
	list->head = node;
	list->tail = node;
  } else {
	node->prev = NULL;
	node->next = list->head;
	list->head->prev = node;
	list->head = node;
  }

  list->len++;

  return node;
}

node_t *insert_back(list_t *list, void *data) {
  if (list->head == NULL) {
	return insert_front(list, data);
  }

  node_t *node = node_create(data);
  node->prev = list->tail;
  node->next = NULL;

  list->tail->next = node;
  list->tail = node;
  list->len++;

  return node;
}

node_t *list_search(list_t *list, void *data) {
  iterator_t *iterator = iterator_from_list(list, LIST_HEAD);

  node_t *node = iterator->next;
  while (node != NULL) {
	if (list->match && list->match(node->data, data)) {
	  iterator_destroy(iterator);
	  return node;
	}
	if (data == node->data) {
	  iterator_destroy(iterator);
	  return node;
	}
	node = iterator_next(iterator);
  }

  return NULL;
}

void list_destroy(list_t *list) {
  node_t *cur = NULL;
  node_t *next = list->head;

  while (next != NULL) {
	cur = next;
	next = next->next;
	free(cur);
  }

  free(list);
}
