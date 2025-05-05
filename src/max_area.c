#include "max_area.h"

typedef struct MAP {
  char **map_matrix;
  unsigned int n_rows;
  unsigned int n_cols;
} map;
typedef struct COORDINATES {
  int x;
  int y;
} coordinate;
typedef struct NODE_INFO {
  coordinate bottom_edge;
  coordinate right_edge;
} node_info;

node_info search_furthest_nodes(map *search_map, int root_row, int root_col) {
  node_info bottom_search;
  node_info right_search;

  // Search recursively starting from the node bellow
  if (root_row == search_map->n_rows - 1 ||
      search_map->map_matrix[root_row + 1][root_col] == 0) {
    bottom_search.bottom_edge.y = root_row;
    bottom_search.bottom_edge.x = root_col;

    bottom_search.right_edge.y = root_row;
    bottom_search.right_edge.x = root_col;
  } else {
    bottom_search = search_furthest_nodes(search_map, root_row + 1, root_col);
  }

  // Search recursively starting from the node on the right
  if (root_col == search_map->n_cols - 1 ||
      search_map->map_matrix[root_row][root_col + 1] == 0) {
    right_search.bottom_edge.y = root_row;
    right_search.bottom_edge.x = root_col;

    right_search.right_edge.y = root_row;
    right_search.right_edge.x = root_col;
  } else {
    right_search = search_furthest_nodes(search_map, root_row, root_col + 1);
  }
}

int calculate_max_area(char **input_matrix, unsigned int M, unsigned int N) {
  map search_map = {
      .map_matrix = input_matrix,
      .n_rows = M,
      .n_cols = N,
  };

  for (int row_index = 0; row_index < M; row_index++) {
    for (int column_index = 0; column_index < N; column_index++) {

      if (input_matrix[row_index][column_index] == 0)
        continue;

      node_info furthest_edge =
          search_furthest_nodes(&search_map, row_index, column_index);
    }
  }
}