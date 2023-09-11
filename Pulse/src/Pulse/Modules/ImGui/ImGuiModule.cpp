#include "pch.h"

#include "Pulse/Modules/ImGui/ImGuiModule.h"

#include <GLFW/glfw3.h>

#include "Pulse/Modules/ModuleManager.h"

namespace Pulse::Modules {

	void ImGuiModule::Initialize() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		imGuiIO_ = &ImGui::GetIO();

		imGuiIO_->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		imGuiIO_->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 430");

		// Add EventListeners via helper class
		imGuiModuleEventListener_ = Events::IEventListener<ImGuiModuleEventListener>::Create(*this, *imGuiIO_);

		window_ = Pulse::Modules::ModuleManager::GetInstance().GetModule<Pulse::Modules::Windows::WindowsWindow>();
	}

	ImGuiModule::ImGuiModuleEventListener::ImGuiModuleEventListener(ImGuiModule& parent, ImGuiIO& imGuiIO)
		: parent_(parent), imGuiIO_(imGuiIO){

		AddListener(Events::Input::MouseMovedEvent, &ImGuiModuleEventListener::OnMouseMoved);
		AddListener(Events::Input::MouseMovedEvent, &ImGuiModuleEventListener::OnMouseScrolled);
	}

	void ImGuiModule::ImGuiModuleEventListener::OnMouseMoved(double xOffset, double yOffset) {
		imGuiIO_.AddMousePosEvent((float)xOffset, (float)yOffset);
	}

	void ImGuiModule::ImGuiModuleEventListener::OnMouseScrolled(double xOffset, double yOffset) {
		imGuiIO_.AddMouseWheelEvent((float)xOffset, (float)yOffset);
	}

	void ImGuiModule::Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiModule::Update() {

		imGuiIO_->DisplaySize = ImVec2((float)window_->GetWidth(), (float)window_->GetHeight());

		float time = (float)glfwGetTime();
		imGuiIO_->DeltaTime = time_ > 0.0f ? (time - time_) : (1.0f / 60.0f);
		time_ = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

} // namespace Pulse::Modules