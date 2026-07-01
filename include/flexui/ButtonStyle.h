// include/flexui/ButtonStyle.h
#pragma once
#include <raylib.h>

struct ButtonStyle {
    Color colorNormal  = {50, 50, 50, 255};
    Color colorHovered = {80, 80, 80, 255};
    Color colorBorder  = WHITE;
    Color colorText    = WHITE;
    float borderWidth  = 2.0f;
    float fontSize     = 0;
    float roundness    = 0.0f;
};

// some presets
namespace ButtonStyles {
    inline ButtonStyle Primary() {
        return {
            .colorNormal  = {0, 120, 215, 255},
            .colorHovered = {0, 150, 255, 255},
            .colorBorder  = {0, 80, 180, 255},
            .colorText    = WHITE,
            .roundness    = 0.3f
        };
    }

    inline ButtonStyle Danger() {
        return {
            .colorNormal  = {200, 50, 50, 255},
            .colorHovered = {230, 80, 80, 255},
            .colorBorder  = {150, 30, 30, 255},
            .colorText    = WHITE,
            .roundness    = 0.3f
        };
    }

    inline ButtonStyle Ghost() {
        return {
            .colorNormal  = {0, 0, 0, 0},
            .colorHovered = {255, 255, 255, 20},
            .colorBorder  = WHITE,
            .colorText    = WHITE,
        };
    }
}
