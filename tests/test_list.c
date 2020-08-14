#include "unity.h"
#include <stdlib.h>

#include "../list.h"
#include "../iterator.h"

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
  insert_back(list, "php");
  insert_back(list, "java");
  insert_back(list, "c#");

  node_t *java = list_search(list, "java");
  node_t *go = insert_after(list, java, "go");
  node_t *csharp = list_search(list, "c#");

  TEST_ASSERT_EQUAL_PTR(java->next, go);
  TEST_ASSERT_EQUAL_PTR(go->prev, java);
  TEST_ASSERT_EQUAL_PTR(go->next, csharp);
  TEST_ASSERT_EQUAL_PTR(csharp->prev, go);

  list_destroy(list);
}

void test_insert_before(void) {
  list_t *list = list_create();
  insert_back(list, "php");
  insert_back(list, "java");
  insert_back(list, "c#");

  node_t *php = list_search(list, "php");
  node_t *java = list_search(list, "java");
  node_t *go = insert_before(list, java, "go");

  TEST_ASSERT_EQUAL_PTR(java->prev, go);
  TEST_ASSERT_EQUAL_PTR(go->prev, php);
  TEST_ASSERT_EQUAL_PTR(go->next, java);
  TEST_ASSERT_EQUAL_PTR(php->next, go);

  list_destroy(list);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_iterator);
  RUN_TEST(test_insert_back);
  RUN_TEST(test_insert_front);
  RUN_TEST(test_list_search);
  RUN_TEST(test_insert_after);
  RUN_TEST(test_insert_before);

  return UNITY_END();
}
