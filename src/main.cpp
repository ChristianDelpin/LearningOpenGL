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

int main()
{
	int width = 1600;
	int height = 900;
	const char* title = "Physics Simulator v0.0.1";
	GLFWmonitor* monitor = nullptr;     // Want to be in windowed mode, so no monitor.
	GLFWwindow* share = nullptr;        // No shared context, idk what that means so just keeping null.

    if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);

    if (!window){
        glfwTerminate();
        return -1;
    }
	glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
		glfwSwapBuffers(window);        // Swap between front and back buffers. Front buffer is what the user currently sees, back buffer is where we draw. Then, we swap them.
		glfwPollEvents();               // Used to process events, like keyboard and mouse input.
    }

	Ball ball;
	ball.mass = 5.0f;
	
	float force = ball.mass * myPhysicsConstants::G;

}