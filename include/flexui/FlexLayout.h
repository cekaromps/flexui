#pragma once
#include <raylib.h>
#include <vector>
#include <functional>

enum class FlexDirection { Row, Column };
enum class FlexAlign    { Start, Center, End, Stretch };
enum class FlexJustify  { Start, Center, End, SpaceBetween };

struct FlexChild {
    float fixedW = -1, fixedH = -1;
    float grow = 0;
    bool visible = true;
    std::function<void(Rectangle)> draw;
    std::function<void(Rectangle)> handleInput;
};

class FlexBox {
public:
    FlexDirection direction = FlexDirection::Column;
    FlexJustify   justify   = FlexJustify::Start;
    FlexAlign     align     = FlexAlign::Stretch;
    float gap     = 8.0f;
    float padding = 0.0f;

    std::vector<FlexChild> children;

    void Add(FlexChild child);
    void Layout(Rectangle bounds);
    void HandleInput(Rectangle bounds);

private:
    struct LayoutResult {
        Rectangle rect;
    };
    std::vector<LayoutResult> ComputeLayout(Rectangle bounds);
};
