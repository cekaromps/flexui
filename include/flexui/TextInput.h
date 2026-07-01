#pragma once
#include "Component.h"
#include <string>

class TextInput : public Component {
public:
    std::string value;
    std::string placeholder;
    int maxLength = 256;
    bool focused = false;
    Font font;

    void HandleInput() override;
    void Draw() override;
};

