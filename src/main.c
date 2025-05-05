#include <stdio.h>
#include "max_area.h"

int main(void) {
  printf("Running...\n");

  char map[5][6] = {
      {0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1},
      {0, 1, 1, 0, 1, 0},
      {0, 0, 1, 0, 1, 0},
  };
  calculate_max_area((char *)map, 5, 6);
  return 0;
}