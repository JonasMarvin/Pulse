#include "pch.h"

#include <glad/glad.h>

// Uses GLFW and OpenGL3 as the backend for ImGui with glad as the OpenGL loader
#ifndef IMGUI_IMPL_OPENGL_LOADER_CUSTOM
	#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif // !IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include "backends/imgui_impl_glfw.cpp"
#include "backends/imgui_impl_opengl3.cpp"