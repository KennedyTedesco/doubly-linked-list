#include <stdlib.h>
#include <string.h>
#include "car.h"

car_t *car_ctor(int year, const char *name) {
  car_t *car = malloc(sizeof(car_t));
  car->name = strdup(name);
  car->year = year;
  return car;
}

void car_dtor(car_t *car) {
  free(car);
}
