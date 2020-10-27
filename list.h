#ifndef DL_LIST_H
#define DL_LIST_H

#include <stdbool.h>

typedef struct node {
  void *data;
  struct node *next;
  struct node *prev;
} node_t;

node_t *node_create(void *data);

typedef void (*list_free_func_t)(const void *);
typedef bool (*list_match_func_t)(const void *, const void *);

typedef struct list {
  node_t *head;
  node_t *tail;
  size_t length;
  list_free_func_t free;
  list_match_func_t match;
} list_t;

list_t *list_create();
void list_reverse(list_t *list);
node_t *list_search(list_t *list, void *data);

node_t *insert_front(list_t *list, void *data);
node_t *insert_back(list_t *list, void *data);
node_t *insert_after(list_t *list, node_t *node, void *data);
node_t *insert_before(list_t *list, node_t *node, void *data);

void delete_first_node(list_t *list);
void delete_last_node(list_t *list);
void delete_node(list_t *list, node_t *node);

void list_destroy(list_t *list);

#endif
