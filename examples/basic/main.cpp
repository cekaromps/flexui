#include <raylib.h>
#include <flexui/FlexLayout.h>
#include <flexui/Button.h>
#include <flexui/TextInput.h>
#include <string>

int main() {
    InitWindow(800, 600, "flexui test");
    SetTargetFPS(60);

    Font font = GetFontDefault();

    // --- setup ---
    FlexBox layout;
    layout.direction = FlexDirection::Column;
    layout.justify   = FlexJustify::Center;
    layout.align     = FlexAlign::Center;
    layout.gap       = 20;
    layout.padding   = 60;

    // label at top
    std::string statusText = "press the button";
    FlexChild labelChild;
    labelChild.fixedH = 40;
    labelChild.draw = [&](Rectangle rect) {
        Vector2 size = MeasureTextEx(font, statusText.c_str(), 24, 1);
        DrawTextEx(font, statusText.c_str(),
            {rect.x + (rect.width - size.x) / 2.0f,
             rect.y + (rect.height - size.y) / 2.0f},
            24, 1, WHITE);
    };
    layout.Add(labelChild);

    // button
    Button btn;
    btn.font    = font;
    btn.label   = "Click me";
    btn.style   = ButtonStyles::Primary();
    btn.onClick = [&]() { statusText = "button clicked!"; };

    FlexChild btnChild;
    btnChild.fixedW = 200;
    btnChild.fixedH = 50;
    btnChild.draw        = [&](Rectangle rect) { btn.rect = rect; btn.Draw(); };
    btnChild.handleInput = [&](Rectangle rect) { btn.rect = rect; btn.HandleInput(); };
    layout.Add(btnChild);

    // text input
    TextInput input;
    input.font        = font;
    input.placeholder = "type something...";

    FlexChild inputChild;
    inputChild.fixedH = 50;
    inputChild.draw        = [&](Rectangle rect) { input.rect = rect; input.Draw(); };
    inputChild.handleInput = [&](Rectangle rect) { input.rect = rect; input.HandleInput(); };
    layout.Add(inputChild);

    // submit button that reads input value
    Button submitBtn;
    submitBtn.font    = font;
    submitBtn.label   = "Submit";
    submitBtn.style   = ButtonStyles::Primary();
    submitBtn.onClick = [&]() {
        statusText = "submitted: " + input.value;
        input.value = "";
    };

    FlexChild submitChild;
    submitChild.fixedW = 200;
    submitChild.fixedH = 50;
    submitChild.draw        = [&](Rectangle rect) { submitBtn.rect = rect; submitBtn.Draw(); };
    submitChild.handleInput = [&](Rectangle rect) { submitBtn.rect = rect; submitBtn.HandleInput(); };
    layout.Add(submitChild);

    // --- loop ---
    while (!WindowShouldClose()) {
        Rectangle screen = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        layout.HandleInput(screen);

        BeginDrawing();
        ClearBackground({30, 30, 30, 255});
        layout.Layout(screen);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
