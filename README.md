# C++ OpenGL 3D Engine

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![OpenGL](https://img.shields.io/badge/OpenGL-Graphics-orange.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

An early-stage C++17 custom built 3D game engine for Windows. 

Written using C++17, OpenGL, GLSL, Dear ImGui, and Lua.

---

## Features

### Currently Implemented Features:
- Basic 3D Rendering
	- GLSL Shader
	- Mesh Rendering
	- Real-Time Lighting System
	- glTF Model Loading Logic
- Texture Load System
- Input Management
- Serialized Scene Management System (support both JSON/Lua)
- First Person Camera System
- Real-Time Physics System
- Custom Editor and Debug Tools
	- Properties Window
	- Console Output Log
	- Profiling Tools
- Main Menu UI System
- Animation System
- Audio System

### Features to be implemented in the future:
- Shadow Mapping
- Multiplatform Support (Mac, Linux)
- Vulkan Support
- ECS-style Architecture

---

## Prerequisites

- C++17 compatible compiler (MSVC, GCC, or Clang)
- OpenGL 4.6
- CMake 3.10

## Third-party libraries

- [bullet3-3.25](https://github.com/bulletphysics/bullet3)
- [cgltf](https://github.com/jkuhlmann/cgltf)
- [freetype-2.14.1](https://github.com/freetype/freetype)
- [glew](https://github.com/nigels-com/glew)
- [glfw-3.4](https://github.com/glfw/glfw)
- [glm-1.0.1](https://github.com/g-truc/glm)
- [imgui-1.92.7](https://github.com/ocornut/imgui)
- [nlohmann/json 3.12.0](https://github.com/nlohmann/json)
- [miniaudio](https://github.com/mackron/miniaudio)
- [stb_image](https://github.com/nothings/stb)
- [lua-5.3.6](https://www.lua.org/)
- [sol2-3.3.0](https://github.com/ThePhD/sol2)

---

## Project Structure
```
cpp-opengl-3d-engine/
├── CMakeLists.txt
├── assets/
│   ├── audio/
│   ├── fonts/
│   ├── materials/
│   ├── models/
│   ├── scenes/
│   ├── shaders/
│   └── textures/
├── engine/
│   ├── CMakeLists.txt
│   ├── docs/
│   ├── source/
│   └── thirdparty/
└── source/
```

* **assets**: audio, fonts, materials, models, scenes, shaders, textures.
* **engine**: core, graphics, components, input, physics, render, …
* **source**: game-related objects.

## Building the Project

```bash
git clone https://github.com/hlee9911/cpp-opengl-3d-engine.git
cd cpp-opengl-3d-engine
mkdir build
cd build
cmake -S .. -B .
```

## Screenshots

(To be added later)

## Status

This project is currently in active development.

## License

This project is licensed under the terms of the [MIT License](LICENSE.md).

---

@2026 Hon Lee
