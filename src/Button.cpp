#include <flexui/Button.h>

void Button::HandleInput() {
    if (!enabled) return;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        if (CheckCollisionPointRec(GetMousePosition(), rect))
            if (onClick) onClick();
}

void Button::Draw() {
    if (!visible) return;
    bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);
    Color bg = hovered ? style.colorHovered : style.colorNormal;

    if (style.roundness > 0)
        DrawRectangleRounded(rect, style.roundness, 8, bg);
    else
        DrawRectangleRec(rect, bg);

    DrawRectangleLinesEx(rect, style.borderWidth, style.colorBorder);

    float fs = style.fontSize > 0 ? style.fontSize : rect.height * 0.5f;
    Vector2 ts = MeasureTextEx(font, label.c_str(), fs, 1);
    DrawTextEx(font, label.c_str(),
        {rect.x + (rect.width  - ts.x) / 2.0f,
         rect.y + (rect.height - ts.y) / 2.0f},
        fs, 1, style.colorText);
}

