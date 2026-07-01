#pragma once
#include "Component.h"
#include <string>
#include <functional>
#include "ButtonStyle.h"

class Button : public Component {
public:
    std::string label;
    Font font;
    std::function<void()> onClick;
    ButtonStyle style;

    void HandleInput() override;
    void Draw()        override;
};

