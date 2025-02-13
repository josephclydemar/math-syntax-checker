#include <stdlib.h>
#include "external/raylib/raylib.h"
#include "core/node.h"


Node_t* create_node(f32 start_pos_x, f32 start_pos_y, f32 radius, Color color, char* desc) {
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    new_node->pos.x = start_pos_x;
    new_node->pos.y = start_pos_y;
    new_node->radius = radius;
    new_node->color = color;
    new_node->description = desc;
    return new_node;
}

void draw_node(const Node_t* const node) {
    DrawRing(node->pos, node->radius + 2.0f, node->radius + 4.0f, 0.0f, 360.0f, 50, node->color);
}