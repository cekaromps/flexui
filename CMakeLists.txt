cmake_minimum_required(VERSION 3.16)
project(flexui VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(flexui STATIC ${SOURCES})

target_include_directories(flexui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE src
)

target_link_libraries(flexui PUBLIC raylib)

# install rules so others can do find_package(flexui)
install(TARGETS flexui EXPORT flexuiTargets
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT flexuiTargets
    FILE flexuiTargets.cmake
    NAMESPACE flexui::
    DESTINATION lib/cmake/flexui
)

# optional: build examples
option(FLEXUI_BUILD_EXAMPLES "Build examples" ON)
if(FLEXUI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

