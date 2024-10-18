#ifndef NODE_H
#define NODE_H

#include "external/raylib/raylib.h"
#include "utils/types.h"

typedef struct {
    Vector2 pos;
    f32 radius;
    Color color;
    char* description;
} Node_t;

Node_t* create_node(f32 start_pos_x, f32 start_pos_y, f32 radius, Color color, char* desc);
void draw_node(const Node_t* const node);

#endif

