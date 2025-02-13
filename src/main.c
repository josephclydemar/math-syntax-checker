
#include "external/raylib/raylib.h"
#include "gui/window.h"
#include "core/diagram.h"

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Math Syntax Checker");
    SetTargetFPS(60);

    Diagram_t* d = create_diagram();

    // Main game loop
    while(!WindowShouldClose()) {       // Detect window close button or ESC key
        BeginDrawing();
        ClearBackground(BLACK);

        get_next_char(d);
        draw_diagram(d);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}