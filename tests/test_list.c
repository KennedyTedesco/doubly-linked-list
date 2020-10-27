#include "unity.h"
#include <stdlib.h>
#include <string.h>

#include "../list.h"
#include "../iterator.h"

typedef struct car {
  int year;
  char *name;
} car_t;

car_t *car_ctor(int year, const char *name) {
  car_t *car = malloc(sizeof(car_t));
  car->name = strdup(name);
  car->year = year;
  return car;
}

void car_dtor(car_t *car) {
  free(car);
}

void setUp(void) {}
void tearDown(void) {}

void test_list_search(void) {
  list_t *list = list_create();

  insert_back(list, "foo");
  insert_back(list, "bar");
  insert_back(list, "php");
  insert_back(list, "go");
  insert_back(list, "rust");

  TEST_ASSERT_EQUAL_STRING("php", list_search(list, "php")->data);
  TEST_ASSERT_EQUAL_STRING("rust", list_search(list, "rust")->data);
  TEST_ASSERT_NULL(list_search(list, "c#"));

  list_destroy(list);
}

void test_iterator(void) {
  list_t *list = list_create();

  int years[] = {2015, 2016, 2017, 2018, 2030};
  insert_back(list, &years[0]);
  insert_back(list, &years[1]);
  insert_back(list, &years[2]);
  insert_back(list, &years[3]);
  insert_back(list, &years[4]);

  iterator_t *iterator = iterator_from_list(list, LIST_HEAD);
  TEST_ASSERT_EQUAL_INT(2015, *(int *)iterator->next->data);
  TEST_ASSERT_EQUAL_INT(2016, *(int *)iterator_next(iterator)->data);
  TEST_ASSERT_EQUAL_INT(2017, *(int *)iterator_next(iterator)->data);
  TEST_ASSERT_EQUAL_INT(2018, *(int *)iterator_next(iterator)->data);
  TEST_ASSERT_EQUAL_INT(2030, *(int *)iterator_next(iterator)->data);

  list_destroy(list);
  iterator_destroy(iterator);
}

void test_insert_front(void) {
  list_t *list = list_create();
  TEST_ASSERT_NULL(list->head);
  TEST_ASSERT_NULL(list->tail);

  insert_front(list, "foo");
  TEST_ASSERT_NULL(list->head->next);
  TEST_ASSERT_NULL(list->head->prev);
  TEST_ASSERT_EQUAL_STRING("foo", list->head->data);
  TEST_ASSERT_EQUAL_STRING("foo", list->tail->data);

  insert_front(list, "bar");
  TEST_ASSERT_EQUAL_STRING("bar", list->head->data);
  TEST_ASSERT_EQUAL_STRING("foo", list->tail->data);

  TEST_ASSERT_EQUAL_STRING("foo", list->head->next->data);
  TEST_ASSERT_NULL(list->head->prev);

  TEST_ASSERT_EQUAL_STRING("bar", list->tail->prev->data);
  TEST_ASSERT_NULL(list->tail->next);

  list_destroy(list);
}

void test_insert_back(void) {
  int values[] = {2, 4, 8};

  node_t *node;
  list_t *list = list_create();
  TEST_ASSERT_EQUAL_INT(0, list->len);

  node = insert_back(list, &values[0]);
  TEST_ASSERT_NULL(node->prev);
  TEST_ASSERT_NULL(node->next);
  TEST_ASSERT_EQUAL_INT(2, *(int *)list->head->data);
  TEST_ASSERT_EQUAL_INT(2, *(int *)list->tail->data);
  TEST_ASSERT_EQUAL_INT(1, list->len);

  node = insert_back(list, &values[1]);
  TEST_ASSERT_NULL(node->next);
  TEST_ASSERT_EQUAL_INT(2, *(int *)node->prev->data);
  TEST_ASSERT_EQUAL_INT(4, *(int *)node->prev->next->data);
  TEST_ASSERT_EQUAL_INT(2, *(int *)list->head->data);
  TEST_ASSERT_EQUAL_INT(4, *(int *)list->tail->data);
  TEST_ASSERT_EQUAL_INT(2, list->len);

  node = insert_back(list, &values[2]);
  TEST_ASSERT_NULL(node->next);
  TEST_ASSERT_EQUAL_INT(4, *(int *)node->prev->data);
  TEST_ASSERT_EQUAL_INT(8, *(int *)node->prev->next->data);
  TEST_ASSERT_EQUAL_INT(2, *(int *)list->head->data);
  TEST_ASSERT_EQUAL_INT(8, *(int *)list->tail->data);
  TEST_ASSERT_EQUAL_INT(3, list->len);

  list_destroy(list);
}

void test_insert_after(void) {
  list_t *list = list_create();

  node_t *php = insert_back(list, "php");
  node_t *java = insert_back(list, "java");
  node_t *csharp = insert_back(list, "c#");

  node_t *go = insert_after(list, csharp, "go");

  TEST_ASSERT_NULL(go->next);
  TEST_ASSERT_EQUAL_PTR(go->prev, csharp);
  TEST_ASSERT_EQUAL_PTR(csharp->next, go);
  TEST_ASSERT_EQUAL_PTR(csharp->prev, java);

  TEST_ASSERT_EQUAL_PTR(list->head, php);
  TEST_ASSERT_EQUAL_PTR(list->tail, go);

  TEST_ASSERT_EQUAL_INT(4, list->len);

  list_destroy(list);
}

void test_insert_before(void) {
  list_t *list = list_create();

  node_t *php = insert_back(list, "php");
  node_t *java = insert_back(list, "java");
  node_t *csharp = insert_back(list, "c#");

  node_t *go = insert_before(list, php, "go");

  TEST_ASSERT_NULL(go->prev);
  TEST_ASSERT_EQUAL_PTR(go->next, php);
  TEST_ASSERT_EQUAL_PTR(php->next, java);
  TEST_ASSERT_EQUAL_PTR(php->prev, go);

  TEST_ASSERT_EQUAL_PTR(list->head, go);
  TEST_ASSERT_EQUAL_PTR(list->tail, csharp);

  TEST_ASSERT_EQUAL_INT(4, list->len);

  list_destroy(list);
}

void test_delete_node(void) {
  list_t *list = list_create();

  node_t *php = insert_back(list, "php");
  node_t *java = insert_back(list, "java");
  node_t *node = insert_back(list, "node");
  node_t *go = insert_back(list, "go");

  TEST_ASSERT_EQUAL_INT(4, list->len);

  delete_node(list, go);
  TEST_ASSERT_EQUAL_INT(3, list->len);
  TEST_ASSERT_EQUAL_PTR(list->tail, node);
  TEST_ASSERT_NULL(node->next);
  TEST_ASSERT_EQUAL_PTR(node->prev, java);

  delete_node(list, php);
  TEST_ASSERT_EQUAL_INT(2, list->len);
  TEST_ASSERT_EQUAL_PTR(list->head, java);
  TEST_ASSERT_NULL(java->prev);
  TEST_ASSERT_EQUAL_PTR(java->next, node);

  delete_node(list, node);
  TEST_ASSERT_EQUAL_INT(1, list->len);
  TEST_ASSERT_EQUAL_PTR(list->head, java);
  TEST_ASSERT_EQUAL_PTR(list->tail, java);

  list_destroy(list);
}

void test_delete_first_and_last(void) {
  list_t *list = list_create();

  node_t *php = insert_back(list, "php");
  node_t *java = insert_back(list, "java");
  node_t *node = insert_back(list, "node");
  node_t *go = insert_back(list, "go");

  TEST_ASSERT_EQUAL_PTR(list->head, php);
  TEST_ASSERT_EQUAL_PTR(list->tail, go);
  TEST_ASSERT_EQUAL_INT(4, list->len);

  delete_first_node(list);
  TEST_ASSERT_EQUAL_INT(3, list->len);
  TEST_ASSERT_EQUAL_PTR(list->head, java);

  delete_last_node(list);
  TEST_ASSERT_EQUAL_INT(2, list->len);
  TEST_ASSERT_EQUAL_PTR(list->tail, node);

  list_destroy(list);
}

void test_delete_with_dynamic_data(void) {
  list_t *list = list_create();
  list->free = (list_free_func_t)&car_dtor;

  insert_back(list, car_ctor(1990, "car_a"));
  insert_back(list, car_ctor(1991, "car_b"));
  insert_front(list, car_ctor(1992, "car_c"));
  insert_front(list, car_ctor(1992, "car_d"));
  TEST_ASSERT_EQUAL_INT(4, list->len);

  delete_last_node(list);
  TEST_ASSERT_EQUAL_INT(3, list->len);

  list_destroy(list);
}

void test_list_reverse(void) {
  list_t *list = list_create();
  node_t *php = insert_back(list, "PHP");
  node_t *java = insert_back(list, "Java");
  node_t *rust = insert_back(list, "Rust");
  node_t *node = insert_back(list, "Node");

  TEST_ASSERT_EQUAL_PTR(list->head, php);
  TEST_ASSERT_EQUAL_PTR(list->head->next, java);
  TEST_ASSERT_EQUAL_PTR(list->tail, node);
  TEST_ASSERT_EQUAL_PTR(list->tail->prev, rust);

  list_reverse(list);

  TEST_ASSERT_EQUAL_PTR(list->head, node);
  TEST_ASSERT_EQUAL_PTR(list->tail, php);

  TEST_ASSERT_EQUAL_PTR(node->prev, NULL);
  TEST_ASSERT_EQUAL_PTR(node->next, rust);
  TEST_ASSERT_EQUAL_PTR(php->next, NULL);
  TEST_ASSERT_EQUAL_PTR(php->prev, java);

  list_destroy(list);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_iterator);
  RUN_TEST(test_insert_back);
  RUN_TEST(test_insert_front);
  RUN_TEST(test_list_search);
  RUN_TEST(test_list_reverse);
  RUN_TEST(test_insert_after);
  RUN_TEST(test_insert_before);
  RUN_TEST(test_delete_node);
  RUN_TEST(test_delete_first_and_last);
  RUN_TEST(test_delete_with_dynamic_data);

  return UNITY_END();
}
