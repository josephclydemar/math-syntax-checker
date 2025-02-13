#ifndef BUTTON_H
#define BUTTON_H

#include "utils/types.h"
#include "shared/common.h"
#include "core/diagram.h"

typedef struct {
    iVec2 pos;
    i32 width;
    i32 height;
    Color color;
    const char* text;
} Button_t;

Button_t* create_button(i32 x, i32 y, i32 w, i32 h, Color color, const char* text);
void draw_button(Button_t* const button);

#endif
