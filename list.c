#include <stdlib.h>

#include "list.h"
#include "iterator.h"

static void free_node(list_t *list, node_t *node) {
  if (list->free != NULL) {
	list->free(node->data);
  }

  free(node);
}

list_t *list_create() {
  list_t *list = malloc(sizeof(list_t));

  if (list == 0) {
	return NULL;
  }

  list->len = 0;
  list->head = NULL;
  list->tail = NULL;
  list->free = NULL;
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

  ++list->len;

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
  ++list->len;

  return node;
}

node_t *insert_after(list_t *list, node_t *node, void *data) {
  if (node->next == NULL) {
	return insert_back(list, data);
  }

  node_t *newNode = node_create(data);
  newNode->prev = node;
  newNode->next = node->next;

  node->next->prev = newNode;
  node->next = newNode;

  ++list->len;

  return newNode;
}

node_t *insert_before(list_t *list, node_t *node, void *data) {
  if (node->prev == NULL) {
	return insert_front(list, data);
  }

  node_t *newNode = node_create(data);
  newNode->next = node;
  newNode->prev = node->prev;

  node->prev->next = newNode;
  node->prev = newNode;

  ++list->len;

  return newNode;
}

node_t *list_search(list_t *list, void *data) {
  iterator_t *iterator = iterator_from_list(list, LIST_HEAD);
  node_t *node = iterator->next;

  while (node != NULL) {
	if ((list->match && list->match(node->data, data))
		|| data == node->data) {
	  break;
	}
	node = iterator_next(iterator);
  }

  iterator_destroy(iterator);

  return node;
}

void delete_node(list_t *list, node_t *node) {
  if (node->prev == NULL) {
	(list->head = node->next)->prev = NULL;
  } else if (node->next == NULL) {
	(list->tail = node->prev)->next = NULL;
  } else {
	node->prev->next = node->next;
	node->next->prev = node->prev;
  }

  --list->len;

  free_node(list, node);
}

void delete_first_node(list_t *list) {
  if (list->head != NULL) {
	delete_node(list, list->head);
  }
}

void delete_last_node(list_t *list) {
  if (list->tail != NULL) {
	delete_node(list, list->tail);
  }
}

void list_destroy(list_t *list) {
  node_t *cur = NULL;
  node_t *next = list->head;

  while (next != NULL) {
	cur = next;
	next = next->next;
	free_node(list, cur);
  }

  free(list);
}
