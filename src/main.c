
#include "external/raylib/raylib.h"
#include "gui/window.h"
#include "core/node.h"
#include "core/path.h"

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Armored Havoc");
    SetTargetFPS(60);

    Node_t* node1 = create_node(500.0f, 100.0f, 10.5f, GREEN, "START STATE");
    Node_t* node2 = create_node(1000.0f, 400.0f, 10.5f, GREEN, "START STATE");
    Path_t* path1 = create_path(node1, node2, VIOLET);

    // Main game loop
    while(!WindowShouldClose()) {       // Detect window close button or ESC key
        BeginDrawing();
        ClearBackground(BLACK);

        draw_path(path1);
        draw_node(node1);
        draw_node(node2);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}