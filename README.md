# ThreeDimensionalSpaceEngine
A small rendering engine built using OpenGL via GLFW and GLM.
## Abstracted Features
- `Buffer`s using any primitive types
- `VertexArray`s, containing `VertexArray::BufferLayout`, which contain `VertexArray::BufferLayout::LayoutObject`, used in creating a vao, to send data to the shader
- `Shader`s, containing a filepath and union support
## Added Features
- `Render`s, which are a collection of `Buffer`s, vertex and index and `VertexArray`s
- `Render3D`s, which are `Render`s and a `Transform`
- `Transform`s, which are a collection of a position (`Vec3`), a scale (`Vec3`) and a rotation (`Quaternion`)
- `Renderer`s & `Renderer3D`s, which send the data in `Render`s to the shader for processing
- `IMaterial`s & `IMaterial3D`s, which are a collection of `Shader`s, uniform values of theirs and a MVP matrix for the 3D kind
- `Texture`s, 2D textures which are loaded on top of a `Render<TexturedShape>`
- `TexturedShape`s, a collection of 2 `Vec2`s, the texture coordinate and a position
- `ShapeGeneration` static class used for loading a `Render3D` from obj and for connecting `Vec2`s in a `Render<TexturedShape>`
## Known Limitations
- 3D objects don't have a texture class of material for textures
- Some errors are not logged
## Requirements
- C++20 compiler
- CMake 3.31+
- OpenGL
- GLFW (`libs/glfw3.lib`)
## Build
```bash
cmake -B build
cmake --build build
```
