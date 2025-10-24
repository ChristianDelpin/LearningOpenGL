// src/main.cpp
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// Simple vertex shader + fragment shader (GLSL)
const char* vs_src = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
void main(){ gl_Position = vec4(aPos, 0.0, 1.0); }
)";
const char* fs_src = R"(
#version 330 core
out vec4 FragColor;
void main(){ FragColor = vec4(0.2, 0.6, 0.9, 1.0); }
)";

static void glfw_error_callback(int error, const char* description){
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main(){
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    // Request OpenGL 3.3 core profile (adjust if you generated glad for another version)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "My OpenGL + ImGui App", nullptr, nullptr);
    if (!window){ glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD\n";
        return 1;
    }
    std::cout << "OpenGL " << glGetString(GL_VERSION) << "\n";

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Simple triangle setup
    float triVerts[] = {
        0.0f,  0.6f,
       -0.5f, -0.4f,
        0.5f, -0.4f
    };
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Shader compile helper
    auto compile = [](GLenum t, const char* src)->GLuint{
        GLuint s = glCreateShader(t);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if(!ok){
            char buf[1024]; glGetShaderInfoLog(s, 1024, NULL, buf);
            std::cerr << "Shader compile error: " << buf << "\n";
        }
        return s;
    };
    GLuint vs = compile(GL_VERTEX_SHADER, vs_src);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fs_src);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glDeleteShader(vs); glDeleteShader(fs);

    bool show_demo = true;
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Simple ImGui window
        ImGui::Begin("Controls");
        ImGui::Text("Hello from ImGui!");
        ImGui::Checkbox("Show ImGui demo", &show_demo);
        ImGui::End();

        if(show_demo) ImGui::ShowDemoWindow(&show_demo);

        // Render
        int display_w, display_h; glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0,0,display_w,display_h);
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prog);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteProgram(prog);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
