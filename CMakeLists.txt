cmake_minimum_required(VERSION 3.14)
project(LearningOpenGL VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------- External directories -------------------
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/external/glad)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

# ------------------- Sources -------------------
set(SOURCES
    src/main.cpp
    ${GLAD_DIR}/src/glad.c

    # ImGui core
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp

    # ImGui backends
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# ---------- Create executable ----------
add_executable(${PROJECT_NAME} ${SOURCES})

# ---------- Remove console window ----------
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
        )
    endif()
endif()

# ---------- Include directories & defines ----------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLAD_DIR}/include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

# ---------- Build GLFW ----------
add_subdirectory(${GLFW_DIR})

# ---------- Link libraries ----------
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${OPENGL_gl_LIBRARY})
else()
    message(FATAL_ERROR "OpenGL not found on this system.")
endif()

# ---------- Compiler warnings ----------
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---------- One-command auto-build ----------
# This target runs automatically whenever CMake is invoked
add_custom_target(build_all ALL
    DEPENDS ${PROJECT_NAME}
    COMMENT "Automatically building ${PROJECT_NAME}..."
)