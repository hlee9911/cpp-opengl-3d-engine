# C++ OpenGL 3D Engine

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![OpenGL](https://img.shields.io/badge/OpenGL-Graphics-orange.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A work-in-progress 3D game engine written in modern C++ using OpenGL.

This engine implements core real-time rendering systems, scene management, physics integration, and a custom editor/debug UI built with ImGui.

---

## ✨ Features

### Rendering
- OpenGL rendering pipeline
- GLSL shader system
- Real-time lighting system
- Material system

### Engine Systems
- Scene management
- FPS-style camera system
- Fully integrated physics system (Bullet Physics)

### Editor & Debug Tools (ImGui)
- Console window (logging + runtime output)
- Properties inspector for GameObjects and components
- Real-time profiler tools
- Memory usages visualization tools

### Assets & Data
- glTF model loading (cgltf)
- Texture loading (stb_image)
- JSON-based scene serialization (nlohmann/json)
- Main menu ui system (freetype)
- Audio system (miniaudio) 

---

## 🧰 Prerequisites

- C++17 compatible compiler
- OpenGL 4.6
- CMake 3.10

## 📦 Third-party libraries

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

---

## 📂 Project Structure
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

## ⚡ Building the Project

```bash
git clone https://github.com/hlee9911/cpp-opengl-3d-engine.git
cd cpp-opengl-3d-engine
mkdir build
cd build
cmake -S .. -B .
```

## 📸 Screenshots

(To be added later)

## 🚧 Status

The engine is currently in active development.

## 📜 License

This project is licensed under the terms of the [MIT License](LICENSE.md).

---

@ 2026 Hon Lee
