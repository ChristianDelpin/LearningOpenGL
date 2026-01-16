# Learning OpenGL

## Things I learned/did

### 2025-10-23: 
- Learned how to set up a basic OpenGL project using CMake and Visual Studio 2022.
- Cloned **[GLFW](https://github.com/glfw/glfw.git)** and **[ImGui](https://github.com/ocornut/imgui.git)** repositories, and set as submodules for easier management.
- Struggled with `CMakeLists.txt` configuration but eventually got it working.
	- Configured CMake to find and link GLFW and ImGui correctly.
- Got a simple window displaying using GLFW that shows the ImGui demo and renders a basic triangle using OpenGL.
- Set up a build directory and configured the project using CMake.
	- Now the build process is literally just a one-liner. :)

### 2026-01-15:
- Pushed changes that I had forgotten to do on 2025-10-23.

### 2026-01-16:
- Began working through the **[LearnOpenGL](https://learnopengl.com/)** tutorial.
- Applied a color to the background using `glClearColor`.
	- Involves clearing the color buffer with `glClear(GL_COLOR_BUFFER_BIT)` each frame.
- Drawing a simple triangle using vertex buffers and shaders.
	- For myself: 
		1. We define our triangle vertices in NDC. 
		2. Then, we send this to the Vertex Shader using a Vertex Buffer Object (VBO) and a Vertex Array Object (VAO).
		3. The VBO is given a large batch of our vertex data, vs sending it one vertex at a time for efficiency (CPU -> GPU is slow, and then GPU also has instant access to this data for drawing purposes).
- Did not start on Fragment Shaders yet.

## Stuff for myself

### Building the Project
- In the root directory, run the following command in the **__Developer PowerShell for VS 2022__**:
  ```sh
  cmake --build build --config Release
  ```
  or for a debug build:
  ```sh
  cmake --build build --config Debug
  ```
