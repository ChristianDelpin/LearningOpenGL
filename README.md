# Learning OpenGL

## Things I learned/did

### 2025-10-23: 
- Learned how to set up a basic OpenGL project using CMake and Visual Studio 2022.
- Cloned GLFW and ImGui repositories, and set as submodules for easier management.
- Struggled with CMakeLists.txt configuration but eventually got it working.
	- Configured CMake to find and link GLFW and ImGui correctly.
- Got a simple window displaying using GLFW and rendered a basic triangle using OpenGL.
- Set up a build directory and configured the project using CMake.
	- Now the build process is literally just a one-liner. :)

## Stuff for myself

### Building the Project
- In the root directory, run the following command in the Developer PowerShell for VS 2022:
  ```sh
  cmake --build build --config Release
  ```
