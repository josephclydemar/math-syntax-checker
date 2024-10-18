#ifndef PATH_H
#define PATH_H

#include "node.h"

typedef struct {
    Vector2 path_points[100];
    const Node_t* start_node;
    const Node_t* end_node;
    Color color;
} Path_t;

Path_t* create_path(const Node_t* const start, const Node_t* const end, Color color);
void draw_path(Path_t* const path);

#endif

