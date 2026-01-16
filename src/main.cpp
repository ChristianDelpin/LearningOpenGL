#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>     // Used for window.

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "physics/physics.h" // Used for my constants for now.
#include "objects/ball.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	int width = 1600;
	int height = 900;
	const char* title = "Physics Simulator v0.0.1";
	GLFWmonitor* monitor = nullptr;     // Want to be in windowed mode, so no monitor.
	GLFWwindow* share = nullptr;        // No shared context, idk what that means so just keeping null.

	if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
	glfwMakeContextCurrent(window); // Must be done before initializing GLAD.

	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// First two parameters are the lower left corner of the viewport, last two are width and height.
	// glViewport x and y are mapped to OpenGL coordinates, which range from -1 to 1 in both axes.
	// so (GLintx = -1) == (left side of window), (GLintx = 0) == (center of x axis), (GLintx = 1) == (right side of window)
	glViewport(0, 0, width, height);





	// Whenever the window is resized, we need to adjust the viewport accordingly.
	// The first param is the window, the second is the function that is called on resize. 
	// In this case, it's just a mini helper function that just calls glViewport with the new width and height.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Simple vertex shader source code written in GLSL.
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n" // 'aPos' is the name of the input variable we will use in the vertex shader. It has 3 components (vec3). in means it's an input to the vertex shader.
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"	// gl_Position is a special variable of type `vec4` that the vertex shader is responsible for setting. We convert `vec3` to `vec4` by calling the `vec4` constructor and passing 1.0 for the w component (aka perspective division).
		"}\0"; // c string null terminator
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	/*
	* shader: shader object to which the source code is to be attached.
	* count:  number of strings in the array we're passing
	* string: the array of pointers to strings containing the source code to be loaded into the shader.
	* length: specifies an array of string lengths. If NULL, strings are assumed to be null-terminated.
	*/
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Bind the source code to the shader object.
	glCompileShader(vertexShader); // Compile the shader in run-time.

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

  

	// This is a simple triangle in normalized device coordinates (NDC).
	// The Z is left at 0.0f to maintain constant depth.
	float myTriangle[] = {
		-0.5f, -0.5f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f, // bottom right
		 0.0f,  0.5f, 0.0f  // top
	};

	// VBO time
	unsigned int VBO;
	glGenBuffers(1, &VBO);	// Generate 1 buffer and store the ID in VBO.
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer to the GL_ARRAY_BUFFER target. Now, any buffer calls we make on GL_ARRAY_BUFFER will be used to configure the currently bound VBO.
	
	/*
	* mode:  specifies target buffer object.
	* size:  size in bytes of the buffer object's new data.
	* data:  specifies pointer to data that will be copied into the buffer. aka data we want to send to the GPU.
	* usage: specifies expected usage pattern of the data.
		* Types of usage:
		* GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		* GL_STATIC_DRAW: the data is set only once and used many times.
		* GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
		* These allow the GPU to optimize data storage and access patterns.

	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(myTriangle), myTriangle, GL_STATIC_DRAW); // Copy the vertex data into the buffer's memory.

	// Vertex Shading Time!


	// This is called the render loop.
	while (!glfwWindowShouldClose(window))
	{
		
		processInput(window);			// Check for input. then manage it.

		// Rendering commands

		// R, G, B, Alpha
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer.

		/*
		* Buffers that we can clear:
		* GL_COLOR_BUFFER_BIT: Clears the color buffer.
		* GL_DEPTH_BUFFER_BIT: Clears the depth buffer.
		* GL_STENCIL_BUFFER_BIT: Clears the stencil buffer.
		*/ 

		/*
		* my color that I wanna test out:
		* glClearColor(56/255.0f, 121/255.0f, 137/255.0f, 1.0f); // #0x387989
		* Good news; it works!.
		*/

		// Call events & swap the buffers
		glfwPollEvents();               // Used to process events, like keyboard and mouse input. Also calls any callback functions we register.
		glfwSwapBuffers(window);        // Swap between front and back buffers. Front buffer is what the user currently sees, back buffer is where we draw. Then, we swap them.
	}

	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}