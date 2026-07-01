#pragma once
#include <raylib.h>

class Component {
    public:
        virtual ~Component() {};
        virtual void HandleInput() {};
        virtual void Update()      {};
        virtual void Draw()        {};

        Rectangle rect = {0,0,0,0};
        bool visible = true;
        bool enabled = true;
};
