#include "max_area.h"

/**
 * @brief Returns the largest value between the two
 * inputs.
 */
#define MAX(a, b) ((a > b) ? (a) : (b))

/**
 * @brief Returns the smallest value between the two
 * inputs.
 */
#define MIN(a, b) ((a < b) ? (a) : (b))

/**
 * @brief Returns the distance between two points, but if
 * the points are the same, return 1 as to avoid issues
 * when calculation area.
 */
#define POINT_DISTANCE(a, b) ((a == b) ? (1) : (a - b + 1))

/**
 * @brief Returns the element in position [row_index][col_index]
 * of a 2d array from its pointer.
 */
#define ACCESS(map, row_index, col_index)                                      \
  (map->map_matrix[(row_index) * map->n_cols + (col_index)])

/**
 * @brief Struct centralizing all the necessary information
 * for the map to search.
 */
typedef struct MAP {
  char *map_matrix;
  unsigned int n_rows;
  unsigned int n_cols;
} map;

/**
 * @brief Struct to represent coordinates on the 2d array.
 *
 */
typedef struct COORDINATES {
  int x;
  int y;
} coordinate;

/**
 * @brief Struct holding the result from left and bottom search for a specific
 * node.
 *
 */
typedef struct NODE_INFO {
  coordinate bottom_edge;
  coordinate right_edge;
} node_info;

/**
 * @brief Get the edge with greatest area.
 *
 * @param coord_1 Coordinates of the first edge to compare
 * @param coord_2 Coordinates of the second edge to compare
 * @param root_row Row index of the root (used as upper edge on area
 * calculation)
 * @param root_col Column index of the root (used as upper edge on area
 * calculation)
 * @return coordinate
 */
coordinate get_edge_with_greatest_area(coordinate coord_1, coordinate coord_2,
                                       int root_row, int root_col) {
  int area_1 =
      POINT_DISTANCE(coord_1.y, root_row) * POINT_DISTANCE(coord_1.x, root_col);
  int area_2 =
      POINT_DISTANCE(coord_2.y, root_row) * POINT_DISTANCE(coord_2.x, root_col);
  return (area_1 > area_2) ? coord_1 : coord_2;
}

/**
 * @brief Filter the 4 resulting edges (2 from bottom search and 2 from right
 * search) considering its limitations and returns a `node_info` struct
 * containing the furthest edge starting on the bottom that is also continuous
 * (no wholes in the resulting rectangle) as well as the edge starting from the
 * right.
 *
 * @param bottom_search_edges Struct containing both the furthest edges from the
 * bottom node search.
 * @param right_search_edges Struct containing both the furthest edges from the
 * right node search.
 * @param root_row Row index of the root (used as upper edge on area
 * calculation)
 * @param root_col Column index of the root (used as upper edge on area
 * calculation)
 * @return node_info
 */
node_info filter_edges(node_info bottom_search_edges,
                       node_info right_search_edges, int root_row,
                       int root_col) {
  node_info resulting_edges;

  int max_y_allowed =
      MAX(bottom_search_edges.bottom_edge.y, bottom_search_edges.right_edge.y);
  int max_x_allowed =
      MAX(right_search_edges.bottom_edge.x, right_search_edges.right_edge.x);

  // To determine which of the edges resulted from the right search to use, we
  // first need to cap the y axis to its maximum allowed
  right_search_edges.right_edge.y =
      MIN(right_search_edges.right_edge.y, max_y_allowed);
  right_search_edges.bottom_edge.y =
      MIN(right_search_edges.bottom_edge.y, max_y_allowed);

  resulting_edges.right_edge = get_edge_with_greatest_area(
      right_search_edges.bottom_edge, right_search_edges.right_edge, root_row,
      root_col);

  // To determine which of the edges resulted from the bottom search to use, we
  // first need to cap the x axis to its maximum allowed
  bottom_search_edges.right_edge.x =
      MIN(bottom_search_edges.right_edge.x, max_x_allowed);
  bottom_search_edges.bottom_edge.x =
      MIN(bottom_search_edges.bottom_edge.x, max_x_allowed);

  resulting_edges.bottom_edge = get_edge_with_greatest_area(
      bottom_search_edges.bottom_edge, bottom_search_edges.right_edge, root_row,
      root_col);

  return resulting_edges;
}

/**
 * @brief Recursively search for the deepest continuous node (i.e connected by
 * 1) by searching both the bottom direction as well as right diraction until
 * the edge of the map or a zero is found. The function returns both the result
 * from the bottom search as well as the right.
 *
 * @param search_map Map to search
 * @param root_row The row index of the root of the search
 * @param root_col The column index of the root of the search
 * @return node_info
 */
node_info search_furthest_nodes(map *search_map, int root_row, int root_col) {
  node_info bottom_search;
  node_info right_search;

  // Search recursively starting from the node bellow
  if (root_row == search_map->n_rows - 1 ||
      ACCESS(search_map, root_row + 1, root_col) == 0) {
    bottom_search.bottom_edge.y = root_row;
    bottom_search.bottom_edge.x = root_col;

    bottom_search.right_edge.y = root_row;
    bottom_search.right_edge.x = root_col;
  } else {
    bottom_search = search_furthest_nodes(search_map, root_row + 1, root_col);
  }

  // Search recursively starting from the node on the right
  if (root_col == search_map->n_cols - 1 ||
      ACCESS(search_map, root_row, root_col + 1) == 0) {
    right_search.bottom_edge.y = root_row;
    right_search.bottom_edge.x = root_col;

    right_search.right_edge.y = root_row;
    right_search.right_edge.x = root_col;
  } else {
    right_search = search_furthest_nodes(search_map, root_row, root_col + 1);
  }

  return filter_edges(bottom_search, right_search, root_row, root_col);
}

int calculate_max_area(char *input_matrix, unsigned int M, unsigned int N) {
  int max_area = 0;
  map search_map = {
      .map_matrix = input_matrix,
      .n_rows = M,
      .n_cols = N,
  };

  for (int row_index = 0; row_index < M; row_index++) {
    for (int column_index = 0; column_index < N; column_index++) {

      if (ACCESS((&search_map), row_index, column_index) == 0)
        continue;

      node_info furthest_edge =
          search_furthest_nodes(&search_map, row_index, column_index);
      int area_1 = POINT_DISTANCE(furthest_edge.bottom_edge.y, row_index) *
                   POINT_DISTANCE(furthest_edge.bottom_edge.x, column_index);
      int area_2 = POINT_DISTANCE(furthest_edge.right_edge.y, row_index) *
                   POINT_DISTANCE(furthest_edge.right_edge.x, column_index);

      max_area = MAX(max_area, MAX(area_1, area_2));
    }
  }

  return max_area;
}