find_package(raylib REQUIRED)

add_executable(basic basic/main.cpp)
target_link_libraries(basic PRIVATE flexui)
