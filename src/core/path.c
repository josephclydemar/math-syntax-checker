#include <stdlib.h>
#include "external/raylib/raylib.h"
#include "utils/types.h"
#include "core/path.h"

/* internal functions */

f32 power(f32 base, u32 exponent) {
    f32 result = 1.0f;
    for(u32 i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

void _set_bezier_path_points(Path_t* const path) {
    f32 start_end_x_diff = path->start_node->pos.x - path->end_node->pos.x;
    f32 start_end_y_diff = path->start_node->pos.y - path->end_node->pos.y;

    Vector2 control_p0, control_p1, control_p2, control_p3;

    control_p0.x = path->start_node->pos.x;
    control_p0.y = path->start_node->pos.y;

    control_p1.x = path->start_node->pos.x + 0.5f * start_end_x_diff;
    control_p1.y = path->start_node->pos.y - 0.5f * start_end_y_diff;

    control_p2.x = path->end_node->pos.x - 0.5f * start_end_x_diff;
    control_p2.y = path->end_node->pos.y + 0.5f * start_end_y_diff;

    control_p3.x = path->end_node->pos.x;
    control_p3.y = path->end_node->pos.y;

    f32 t = 0.0f;
    for(i32 i = 0; i < 100; ++i) {
        path->path_points[i].x = power(1.0f-t, 3)*control_p0.x + 3.0f*power(1.0f-t, 2)*t*control_p1.x + 3.0f*(1.0f-t)*power(t, 2)*control_p2.x + power(t, 3)*control_p3.x;
        path->path_points[i].y = power(1.0f-t, 3)*control_p0.y + 3.0f*power(1.0f-t, 2)*t*control_p1.y + 3.0f*(1.0f-t)*power(t, 2)*control_p2.y + power(t, 3)*control_p3.y;
        t += 0.01f;
    }
}

/* ****************** */


Path_t* create_path(const Node_t* const start, const Node_t* const end, Color color) {
    Path_t* new_path = (Path_t*)malloc(sizeof(Path_t));
    new_path->start_node = start;
    new_path->end_node = end;
    
    _set_bezier_path_points(new_path);
    new_path->color = color;

    return new_path;
}

void draw_path(Path_t* const path) {
    DrawSplineLinear(path->path_points, 100, 1.0f, path->color);
    DrawCircle(path->path_points[99].x, path->path_points[99].y, 4.0f, path->color);
}

