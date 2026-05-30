cmake_minimum_required(VERSION 3.31)
project(Raytracing)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

include_directories(include)

add_executable(Raytracing
        main.cpp
        include/glad.c
        helper/VecSpherical.cpp
        helper/VecSpherical.h
        app/App.cpp
        app/App.h
        helper/HelperVectors.h
        helper/Direction.h
        app/Buffer.h
        app/Helper.h
        app/ShaderMethods.h
        app/ShaderMethods.cpp
)

target_link_libraries(Raytracing PRIVATE
        OpenGL::GL
        ${CMAKE_SOURCE_DIR}/libs/glfw3.lib
)