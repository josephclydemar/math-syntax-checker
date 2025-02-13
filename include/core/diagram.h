#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "core/node.h"
#include "core/path.h"

typedef struct {
    struct {
        Vector2 pos;
        Node_t* pointed;
    } current_state;
    char expression_buffer[20];
    u32 char_count;

    Node_t* accept_node;
    Node_t* wait_node;
    Node_t* dead_node;

    Path_t* accept_to_accept_path;
    Path_t* dead_to_dead_path;

    Path_t* accept_to_wait_path;
    Path_t* wait_to_accept_path;
    Path_t* accept_to_dead_path;
    Path_t* wait_to_dead_path;
} Diagram_t;

void get_next_char(Diagram_t* const diagram);
Diagram_t* create_diagram(void);
void draw_diagram(Diagram_t* const diagram);


#endif

