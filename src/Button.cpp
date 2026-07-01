#include <flexui/Button.h>
#include <raylib.h>

void Button::HandleInput() {
    if(!enabled) return;
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        if(CheckCollisionPointRec(GetMousePosition(), rect))
            if(onClick) onClick();
}

void Button::Draw() {
    if (!visible) return;
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    Color bg = hovered ? colorHovered : colorNormal;

    if (roundness > 0)
        DrawRectangleRounded(rect, roundness, 8, bg);
    else
        DrawRectangleRec(rect, bg);

    DrawRectangleLinesEx(rect, borderWidth, colorBorder);

    float fs = fontSize > 0 ? fontSize : rect.height * 0.5f;
    Vector2 ts = MeasureTextEx(font, label.c_str(), fs, 1);
    DrawTextEx(font, label.c_str(),
        {rect.x + (rect.width  - ts.x) / 2.0f,
         rect.y + (rect.height - ts.y) / 2.0f},
        fs, 1, colorText);
}

