# C++ OpenGL 3D Engine

A work-in-progress 3D game engine written in modern C++ using OpenGL.

This project explores low-level graphics programming, rendering pipelines, and engine architecture while implementing core engine systems such as scene management, materials, physics integration, and shader-based rendering.


## Features

- OpenGL-based rendering pipeline
- GLSL shader system
- Component-based GameObject architecture
- Scene management (WIP)
- FPS-style style Camera system
- Real-time lighting
- Model loading using glTF
- Physics integration using Bullet (WIP)
- JSON-based scene loading


## Tech Stack

- C++
- OpenGL
- GLSL
- CMake

Third-party libraries used:

- Bullet Physics Engine
- cgltf (glTF loader)
- stb_image (texture loading)
- nlohmann/json (data serialization)


## Engine Systems

The engine currently includes:

- Window and context management
- Rendering system
- Material and shader pipeline
- Scene and GameObject hierarchy
- FPS-style Camera system
- Parial physics integration


## Building

Requirements:

- C++17 compatible compiler
- CMake
- OpenGL

Build steps:

```plaintext
mkdir build
cd build
cmake ..
cmake -S .. -B .
```

---
Note: The project is currently **in development**.
