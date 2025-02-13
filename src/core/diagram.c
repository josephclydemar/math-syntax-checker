#include <stdlib.h>
#include <string.h>
#include "gui/window.h"
#include "core/diagram.h"

void validate_sequence(Diagram_t* const diagram, char c) {
    if(diagram->current_state.pointed == diagram->accept_node) {
        if(c >= 48 && c <= 57) {
            diagram->current_state.pointed = diagram->accept_node;
            diagram->current_state.pos.x = diagram->accept_node->pos.x;
            diagram->current_state.pos.y = diagram->accept_node->pos.y;
        } else if(c == '+' || c == '-' || c == '*' || c == '/') {
            diagram->current_state.pointed = diagram->wait_node;
            diagram->current_state.pos.x = diagram->wait_node->pos.x;
            diagram->current_state.pos.y = diagram->wait_node->pos.y;
        } else {
            diagram->current_state.pointed = diagram->dead_node;
            diagram->current_state.pos.x = diagram->dead_node->pos.x;
            diagram->current_state.pos.y = diagram->dead_node->pos.y;
        }
    }
    else if(diagram->current_state.pointed == diagram->wait_node) {
        if(c >= 48 && c <= 57) {
            diagram->current_state.pointed = diagram->accept_node;
            diagram->current_state.pos.x = diagram->accept_node->pos.x;
            diagram->current_state.pos.y = diagram->accept_node->pos.y;
        } else {
            diagram->current_state.pointed = diagram->dead_node;
            diagram->current_state.pos.x = diagram->dead_node->pos.x;
            diagram->current_state.pos.y = diagram->dead_node->pos.y;
        }
    }
    else {
        diagram->current_state.pointed = diagram->dead_node;
        diagram->current_state.pos.x = diagram->dead_node->pos.x;
        diagram->current_state.pos.y = diagram->dead_node->pos.y;
    }
}

void get_next_char(Diagram_t* const diagram) {
    char c = '\0';

    if(IsKeyPressed(KEY_A)) c = 'A';
    else if(IsKeyPressed(KEY_B)) c = 'B';
    else if(IsKeyPressed(KEY_C)) c = 'C';
    else if(IsKeyPressed(KEY_D)) c = 'D';
    else if(IsKeyPressed(KEY_E)) c = 'E';
    else if(IsKeyPressed(KEY_F)) c = 'F';
    else if(IsKeyPressed(KEY_G)) c = 'G';
    else if(IsKeyPressed(KEY_H)) c = 'H';
    else if(IsKeyPressed(KEY_I)) c = 'I';
    else if(IsKeyPressed(KEY_J)) c = 'J';
    else if(IsKeyPressed(KEY_K)) c = 'K';
    else if(IsKeyPressed(KEY_L)) c = 'L';
    else if(IsKeyPressed(KEY_M)) c = 'M';
    else if(IsKeyPressed(KEY_N)) c = 'N';
    else if(IsKeyPressed(KEY_O)) c = 'O';
    else if(IsKeyPressed(KEY_P)) c = 'P';
    else if(IsKeyPressed(KEY_Q)) c = 'Q';
    else if(IsKeyPressed(KEY_R)) c = 'R';
    else if(IsKeyPressed(KEY_S)) c = 'S';
    else if(IsKeyPressed(KEY_T)) c = 'T';
    else if(IsKeyPressed(KEY_U)) c = 'U';
    else if(IsKeyPressed(KEY_V)) c = 'V';
    else if(IsKeyPressed(KEY_W)) c = 'W';
    else if(IsKeyPressed(KEY_X)) c = 'X';
    else if(IsKeyPressed(KEY_Y)) c = 'Y';
    else if(IsKeyPressed(KEY_Z)) c = 'Z';

    else if(IsKeyPressed(KEY_ZERO)) c = '0';
    else if(IsKeyPressed(KEY_ONE)) c = '1';
    else if(IsKeyPressed(KEY_TWO)) c = '2';
    else if(IsKeyPressed(KEY_THREE)) c = '3';
    else if(IsKeyPressed(KEY_FOUR)) c = '4';
    else if(IsKeyPressed(KEY_FIVE)) c = '5';
    else if(IsKeyPressed(KEY_SIX)) c = '6';
    else if(IsKeyPressed(KEY_SEVEN)) c = '7';
    else if(IsKeyPressed(KEY_EIGHT)) c = '8';
    else if(IsKeyPressed(KEY_NINE)) c = '9';

    else if(IsKeyPressed(KEY_KP_0)) c = '0';
    else if(IsKeyPressed(KEY_KP_1)) c = '1';
    else if(IsKeyPressed(KEY_KP_2)) c = '2';
    else if(IsKeyPressed(KEY_KP_3)) c = '3';
    else if(IsKeyPressed(KEY_KP_4)) c = '4';
    else if(IsKeyPressed(KEY_KP_5)) c = '5';
    else if(IsKeyPressed(KEY_KP_6)) c = '6';
    else if(IsKeyPressed(KEY_KP_7)) c = '7';
    else if(IsKeyPressed(KEY_KP_8)) c = '8';
    else if(IsKeyPressed(KEY_KP_9)) c = '9';

    else if(IsKeyPressed(KEY_KP_ADD)) c = '+';
    else if(IsKeyPressed(KEY_KP_SUBTRACT)) c = '-';
    else if(IsKeyPressed(KEY_KP_MULTIPLY)) c = '*';
    else if(IsKeyPressed(KEY_KP_DIVIDE)) c = '/';

    if(c != '\0') {
        if(diagram->char_count < 19) {
            validate_sequence(diagram, c);
            diagram->expression_buffer[diagram->char_count] = c;
            diagram->char_count++;
            return;
        }
        for(u32 i = 0; i < 18; ++i) {
            diagram->expression_buffer[i] = diagram->expression_buffer[i+1];
        }
        validate_sequence(diagram, c);
        diagram->expression_buffer[18] = c;
    }
}

Diagram_t* create_diagram(void) {
    Diagram_t* new_diagram = (Diagram_t*)malloc(sizeof(Diagram_t));
    
    memset(new_diagram->expression_buffer, 0, 20);
    new_diagram->char_count = 0;

    new_diagram->accept_node = create_node(100.0f, 350.0f, 20.0f, GREEN, "ACCEPT");
    new_diagram->wait_node = create_node(550.0f, 350.0f, 20.0f, VIOLET, "WAIT");
    new_diagram->dead_node = create_node(1100.0f, 350.0f, 20.0f, BROWN, "DEAD");
    
    new_diagram->accept_to_accept_path = create_path(new_diagram->accept_node, new_diagram->accept_node, LIME);
    new_diagram->dead_to_dead_path = create_path(new_diagram->dead_node, new_diagram->dead_node, LIGHTGRAY);
    
    new_diagram->accept_to_wait_path = create_path(new_diagram->accept_node, new_diagram->wait_node, PINK);
    new_diagram->wait_to_accept_path = create_path(new_diagram->wait_node, new_diagram->accept_node, RED);
    new_diagram->accept_to_dead_path = create_path(new_diagram->accept_node, new_diagram->dead_node, BLUE);
    new_diagram->wait_to_dead_path = create_path(new_diagram->wait_node, new_diagram->dead_node, WHITE);

    new_diagram->current_state.pointed = new_diagram->accept_node;
    new_diagram->current_state.pos.y = new_diagram->accept_node->pos.y;
    new_diagram->current_state.pos.x = new_diagram->accept_node->pos.x;

    return new_diagram;
}

void draw_diagram(Diagram_t* const diagram) {
    draw_node(diagram->accept_node);
    draw_node(diagram->wait_node);
    draw_node(diagram->dead_node);

    draw_path(diagram->accept_to_accept_path);
    draw_path(diagram->dead_to_dead_path);

    draw_path(diagram->accept_to_wait_path);
    draw_path(diagram->wait_to_accept_path);
    draw_path(diagram->accept_to_dead_path);
    draw_path(diagram->wait_to_dead_path);

    DrawRing(diagram->current_state.pos, 6.0f, 16.0f, 0.0f, 360.0f, 50, BLUE);
    DrawText(diagram->expression_buffer, 50, WINDOW_HEIGHT - 50, 40, WHITE);
}
