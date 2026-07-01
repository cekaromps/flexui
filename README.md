# flexui
A simple flex-layout UI library for raylib.

## Requirements
- raylib 5.0+
- C++20
- CMake 3.16+

## Integration

### FetchContent (recommended)
```cmake
include(FetchContent)
FetchContent_Declare(
    flexui
    GIT_REPOSITORY https://github.com/cekaromps/flexui.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(flexui)
target_link_libraries(your_app PRIVATE flexui)
```

### add_subdirectory
```cmake
add_subdirectory(external/flexui)
target_link_libraries(your_app PRIVATE flexui)
```

## Usage
```cpp
#include <flexui/FlexLayout.h>
#include <flexui/Button.h>
#include <flexui/TextInput.h>

FlexBox layout;
layout.direction = FlexDirection::Column;
layout.gap       = 20;

FlexChild btn;
btn.fixedH = 50;
btn.draw = [](Rectangle rect) {
    DrawRectangleRec(rect, RED);
};
layout.Add(btn);

layout.Layout({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()});
```

## License
MIT

