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
		3. The VBO is given a large batch of our vertex data, vs sending it one vertex at a time for efficiency (CPU → GPU is slow, and then GPU also has instant access to this data for drawing purposes).
- Did not start on Fragment Shaders yet.

### 2026-07-24
A bit of a hiatus to finish up my degree, and a bit of a programming break.

- Reviewed my notes to remind myself of how things work, and what I've done so far.
- Learned what an **alpha** value is
	- Transparency level of an object


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

### Terms and Concepts

#### Graphics Pipeline
1. Vertex Shader
	- Takes a collection of vertices, and maps them to NDC
2. Geometry Shader (optional)
	- Connects the vertices together to form primitive shapes (triangles, lines, etc.)
		- Not sure, but from the simple image example, it looks like it does so via nearest neighbors.
3. Primitive Shape Assembly
	- Takes the primitives, and bounds the shape (sets the perimiter of the shape)
4. Rasterization
	- Maps the bounds to the device's pixel
	- Fills in the mapped pixels 
	- Performs **clipping**: discards any pixels that are out of view (occluded objects, or outside the POV)
5. Fragment Shader
	- Calculates the final color of a pixel
	- Contains data about the scene such as lighting, textures, shadows, etc.
6. Alpha Tests & Blending
	- Checks the **depth** and **stencil** values
	- Performs further clipping
X. Secret Stages: Tesselation and Transformation Feedback Loop
	- idk about them, but they're mentioned in the tutorial. Writing them down so I can refer to them later if discussed.

The primary stages that are worked with are (1) and (5) to create the object shapes, and the cool effects on them. They are also **required** to be defined/implemented. ***There are no default vertex/fragment shaders on the GPU**

#### Definitions
- **NDC**: Normalized Device Coordinates
- **VBO**: Vertex Buffer Object
	- On-GPU memory that stores the vertex data. Advantage: allows us to send large batches of vertex data to the GPU
- **VAO**: Vertex Array Object
- **Alpha**: Transparency level of an object
