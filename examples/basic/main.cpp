#include <raylib.h>
#include <flexui/FlexLayout.h>
#include <flexui/Button.h>
#include <flexui/TextInput.h>

int main() {
    InitWindow(800, 600, "flexui basic example");
    SetTargetFPS(60);

    Font font = LoadFontEx("font.ttf", 32, nullptr, 0);

    FlexBox layout;
    layout.direction = FlexDirection::Column;
    layout.justify   = FlexJustify::Center;
    layout.align     = FlexAlign::Center;
    layout.gap       = 20;
    layout.padding   = 40;

    Button btn;
    btn.font  = font;
    btn.label = "Click me";
    btn.style = ButtonStyles::Primary();
    btn.onClick = []() { TraceLog(LOG_INFO, "clicked!"); };

    TextInput input;
    input.font        = font;
    input.placeholder = "Type something...";

    FlexChild btnChild;
    btnChild.fixedW = 200;
    btnChild.fixedH = 50;
    btnChild.draw        = [&](Rectangle rect) { btn.rect = rect; btn.Draw(); };
    btnChild.handleInput = [&](Rectangle rect) { btn.rect = rect; btn.HandleInput(); };
    layout.Add(btnChild);

    FlexChild inputChild;
    inputChild.fixedH = 50;
    inputChild.draw        = [&](Rectangle rect) { input.rect = rect; input.Draw(); };
    inputChild.handleInput = [&](Rectangle rect) { input.rect = rect; input.HandleInput(); };
    layout.Add(inputChild);

    while (!WindowShouldClose()) {
        Rectangle screen = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        layout.HandleInput(screen);

        BeginDrawing();
        ClearBackground({30, 30, 30, 255});
        layout.Layout(screen);
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
}
