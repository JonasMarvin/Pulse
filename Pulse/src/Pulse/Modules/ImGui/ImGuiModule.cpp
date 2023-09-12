#include "pch.h"

#include "Pulse/Modules/ImGui/ImGuiModule.h"

// TODO: Remove glfw and glad here and move functionality to own modules
#include <GLFW/glfw3.h> 
#include <glad/glad.h>

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
		AddListener(Events::Input::ScrollEvent , &ImGuiModuleEventListener::OnMouseScrolled);
		AddListener(Events::Input::MouseEvent, &ImGuiModuleEventListener::OnMouseButton);
		AddListener(Events::Input::KeyEvent, &ImGuiModuleEventListener::OnKey);
		AddListener(Events::Input::CharEvent, &ImGuiModuleEventListener::OnChar);
		AddListener(Events::Window::WindowResizeEvent, &ImGuiModuleEventListener::OnWindowResize);
	}

	void ImGuiModule::ImGuiModuleEventListener::OnMouseMoved(double xOffset, double yOffset) {
		imGuiIO_.AddMousePosEvent(static_cast<float>(xOffset), static_cast<float>(yOffset));
	}

	void ImGuiModule::ImGuiModuleEventListener::OnMouseScrolled(double xOffset, double yOffset) {
		imGuiIO_.AddMouseWheelEvent(static_cast<float>(xOffset), static_cast<float>(yOffset));
	}

	void ImGuiModule::ImGuiModuleEventListener::OnMouseButton(int button, int action, int mods) {
		if (action == GLFW_REPEAT) {
			return;
		}
		else if (action == GLFW_RELEASE) {
			imGuiIO_.AddMouseButtonEvent(button, false);
		}
		else if(action == GLFW_PRESS) {
			imGuiIO_.AddMouseButtonEvent(button, true);
		}
	}

	void ImGuiModule::ImGuiModuleEventListener::OnKey(int key, int scancode, int action, int mods) {
		// TODO: Inputsystem
	}

	void ImGuiModule::ImGuiModuleEventListener::OnChar(unsigned int character) {
		// TODO: Inputsystem
	}

	void ImGuiModule::ImGuiModuleEventListener::OnWindowResize(int width, int height) {
		imGuiIO_.DisplaySize = ImVec2((float)width, (float)height);
		imGuiIO_.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, width, height);
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