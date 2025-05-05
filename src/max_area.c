#include "max_area.h"

/**
 * @brief Returns the largest value between  the two
 * inputs.
 */
#define MAX(a, b) ((a > b) ? a : b)

/**
 * @brief Returns the distance between two points, but if
 * the points are the same, return 1 as to avoid issues
 * when calculation area.
 */
#define POINT_DISTANCE(a, b) ((a == b) ? 1 : a - b)
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

coordinate get_edge_with_greatest_area(coordinate coord_1, coordinate coord_2,
                                       int root_row, int root_col) {
  int area_1 =
      POINT_DISTANCE(root_row, coord_1.y) * POINT_DISTANCE(root_col, coord_1.x);
  int area_2 =
      POINT_DISTANCE(root_row, coord_2.y) * POINT_DISTANCE(root_col, coord_2.x);
  return (area_1 > area_2) ? coord_1 : coord_2;
}

node_info filter_edges(node_info bottom_search_edges,
                       node_info right_search_edges, int root_row,
                       int root_col) {
  node_info resulting_edges;

  int max_y_allowed =
      MAX(bottom_search_edges.bottom_edge.y, bottom_search_edges.right_edge.y);
  int max_x_allowed =
      MAX(right_search_edges.bottom_edge.x, right_search_edges.right_edge.x);

  // To determine which of the edges resulted from the right search to use, we
  // first need to disconsider any that have a y coord greater than the allowed
  // by the search results from the bottom nodes
  if (right_search_edges.bottom_edge.y > max_y_allowed)
    resulting_edges.right_edge = right_search_edges.right_edge;
  else if (right_search_edges.right_edge.y > max_y_allowed)
    resulting_edges.right_edge = right_search_edges.bottom_edge;
  else
    resulting_edges.right_edge = get_edge_with_greatest_area(
        right_search_edges.bottom_edge, right_search_edges.right_edge, root_row,
        root_col);

  // To determine which of the edges resulted from the bottom search to use, we
  // first need to disconsider any that have a x coord greater than the allowed
  // by the search results from the right nodes
  if (bottom_search_edges.right_edge.x > max_x_allowed)
    resulting_edges.bottom_edge = bottom_search_edges.bottom_edge;
  else if (bottom_search_edges.bottom_edge.x > max_x_allowed)
    resulting_edges.bottom_edge = bottom_search_edges.right_edge;
  else
    resulting_edges.bottom_edge = get_edge_with_greatest_area(
        bottom_search_edges.bottom_edge, bottom_search_edges.right_edge,
        root_row, root_col);

  return resulting_edges;
}

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

  return filter_edges(bottom_search, right_search, root_row, root_col);
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
      int area_1 = POINT_DISTANCE(row_index, furthest_edge.bottom_edge.y) *
                   POINT_DISTANCE(column_index, furthest_edge.bottom_edge.x);
      int area_2 = POINT_DISTANCE(row_index, furthest_edge.right_edge.y) *
                   POINT_DISTANCE(column_index, furthest_edge.right_edge.x);

      max_area = MAX(max_area, MAX(area_1, area_2));
    }
  }
}