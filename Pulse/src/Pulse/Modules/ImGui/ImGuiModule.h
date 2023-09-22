#pragma once

#include "Pulse/Modules/IRenderImGuiModule.h"

// Uses GLFW and OpenGL3 as the backend for ImGui with glad as the OpenGL loader
#ifndef IMGUI_IMPL_OPENGL_LOADER_CUSTOM
	#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif // !IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Pulse::Modules {

	// class to manage the imgui functionality
	class ImGuiModule : public IRenderImGuiModule {
	public:
		void Initialize() override; // function to initialize the module
		void Shutdown() override; // function to shutdown the module
		void RenderImGui() override; // function to update the ImGui rendering
		void BeginFrame(); // function to update the ImGui IO object at the beginning of the frame
		void EndFrame(); // function to update the ImGui IO object at the end of the frame

	private:
		ImGuiModule() : imGuiIO_(nullptr), window_(nullptr) {}// private constructor to prevent creation of the module outside of the module manager
		~ImGuiModule() = default; // private destructor to prevent deletion of the module outside of the module manager

		GLFWwindow* window_; // pointer to the GLFW window to allow faster access to the GLFW window
		ImGuiIO* imGuiIO_; // pointer to the ImGui IO object to allow faster access to the ImGui IO object
		float time_ = 0.0f; // time since the module was last updated

		friend class ModuleManager; // friend class to allow the module manager to create and manage the window
	}; // class ImGuiModule

} // namespace Pulse::Modules