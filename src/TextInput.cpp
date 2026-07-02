#include <flexui/TextInput.h>

void TextInput::HandleInput() {
    if (!enabled) return;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        focused = CheckCollisionPointRec(GetMousePosition(), rect);
    if (!focused) return;
    if (IsKeyPressed(KEY_BACKSPACE) && !value.empty())
        value.pop_back();

    bool ctrlDown = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
    if (ctrlDown && IsKeyPressed(KEY_V)) {
        const char* clip = GetClipboardText();
        if (clip) {
            for (const char* p = clip; *p != '\0'; ++p) {
                // Treat newlines/tabs as terminators rather than inserting
                // them into a single-line field.
                if (*p == '\n' || *p == '\r' || *p == '\t') break;
                if ((int)value.size() >= maxLength) break;
                value += *p;
            }
        }
    }

    int ch = GetCharPressed();
    while (ch > 0) {
        if (ch >= 32 && (int)value.size() < maxLength)
            value += (char)ch;
        ch = GetCharPressed();
    }
}

void TextInput::Draw() {
    if (!visible) return;
    DrawRectangleRec(rect, {30, 30, 30, 255});
    DrawRectangleLinesEx(rect, 2, focused ? WHITE : GRAY);
    float fs = rect.height * 0.55f;
    float padding = 8.0f;
    const char* display = value.empty() ? placeholder.c_str() : value.c_str();
    Color col = value.empty() ? GRAY : WHITE;
    DrawTextEx(font, display,
        {rect.x + padding, rect.y + (rect.height - fs) / 2.0f},
        fs, 1, col);
    if (focused && (int)(GetTime() * 2) % 2 == 0) {
        Vector2 ts = MeasureTextEx(font, value.c_str(), fs, 1);
        float cx = rect.x + padding + ts.x + 2;
        float cy = rect.y + (rect.height - fs) / 2.0f;
        DrawLineEx({cx, cy}, {cx, cy + fs}, 2, WHITE);
    }
}
