#include <stdio.h>
#include "max_area.h"

int main(void) {
  printf("Running...\n");
  char map[4][5] = {
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0}
  };

  calculate_max_area((char *)map, 4, 5);

  return 0;
}