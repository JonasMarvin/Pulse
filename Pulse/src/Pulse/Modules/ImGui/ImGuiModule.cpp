#include "pch.h"

#include "Pulse/Modules/ImGui/ImGuiModule.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Window/WindowModule.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Pulse::Modules {

	void ImGuiModule::Initialize() {

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		imGuiIO_ = &ImGui::GetIO();
		imGuiIO_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		// imGuiIO_->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls // TODO: Add gamepad detection to be able to set the backend flag
		imGuiIO_->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		imGuiIO_->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		// imGuiIO_->ConfigViewportsNoAutoMerge = true;
		// imGuiIO_->ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (imGuiIO_->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		window_ = static_cast<GLFWwindow*>(ModuleManager::GetInstance().GetModule<WindowModule>()->GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window_, true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}

	void ImGuiModule::Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiModule::RenderImGui() {
		
	}

	void ImGuiModule::BeginFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiModule::EndFrame() {
		// Actualize ImGui windows
		imGuiIO_->DisplaySize = ImVec2(static_cast<float>(ModuleManager::GetInstance().GetModule<WindowModule>()->GetWidth()), static_cast<float>(ModuleManager::GetInstance().GetModule<WindowModule>()->GetHeight()));

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (imGuiIO_->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

} // namespace Pulse::Modules