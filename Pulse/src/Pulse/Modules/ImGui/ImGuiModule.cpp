#include "pch.h"

#include "Pulse/Modules/ImGui/ImGuiModule.h"

#include <GLFW/glfw3.h>
#include "Pulse/Modules/ImGui/OpenGL/ImGuiOpenGLRenderer.h"
#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Window/Platform/Windows/WindowsWindow.h"

namespace Pulse::Modules {

	void ImGuiModule::Initialize() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 430");

	}

	void ImGuiModule::Shutdown() {
		
	}

	void ImGuiModule::Update() {

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)Pulse::Modules::ModuleManager::GetInstance().GetModule<Pulse::Modules::Windows::WindowsWindow>()->GetWidth(), (float)Pulse::Modules::ModuleManager::GetInstance().GetModule<Pulse::Modules::Windows::WindowsWindow>()->GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = time_ > 0.0f ? (time - time_) : (1.0f / 60.0f);
		time_ = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

} // namespace Pulse::Modules