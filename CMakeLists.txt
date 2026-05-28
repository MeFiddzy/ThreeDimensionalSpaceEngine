cmake_minimum_required(VERSION 3.31)
project(Raytracing)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

include_directories(include)

add_executable(Raytracing
        main.cpp
        include/glad.c
        math_physics/VecSpherical.cpp
        math_physics/VecSpherical.h
        app/App.cpp
        app/App.h
        math_physics/HelperVectors.h
)

target_link_libraries(Raytracing PRIVATE
        OpenGL::GL
        ${CMAKE_SOURCE_DIR}/libs/glfw3.lib
)