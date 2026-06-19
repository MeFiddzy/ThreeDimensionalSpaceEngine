cmake_minimum_required(VERSION 3.31)
project(ThreeDimensionalSpaceEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

include_directories(include)

add_executable(ThreeDimensionalSpaceEngine
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
        app/VertexArray.cpp
        app/VertexArray.h
        app/Renderer.cpp
        app/Renderer.h
        app/Render.h
        helper/HelperVector.cpp
)

target_link_libraries(ThreeDimensionalSpaceEngine PRIVATE
        OpenGL::GL
        ${CMAKE_SOURCE_DIR}/libs/glfw3.lib
)