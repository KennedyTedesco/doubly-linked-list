#ifndef DL_LIST_TESTS_CAR_H
#define DL_LIST_TESTS_CAR_H

typedef struct car {
  int year;
  char *name;
} car_t;

void car_dtor(car_t *car);
car_t *car_ctor(int year, const char *name);

#endif
