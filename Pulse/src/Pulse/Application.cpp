#include "pch.h"

#include "Application.h"

#include "Pulse/Modules/Window/Platform/Windows/WindowsWindow.h"
#include "Pulse/Modules/Input/Platform/Windows/WindowsInput.h"
#include "Pulse/Modules/ImGui/ImGuiModule.h"
#include "Pulse/Modules/Rendering/Renderer.h"
#include "Pulse/Modules/Camera/Camera.h"

namespace Pulse {
		
	Application::ApplicationEventListener::ApplicationEventListener(Application& application)
		: parentApplication_(application) {
		AddListener(Events::Window::WindowCloseEvent ,&ApplicationEventListener::OnWindowClose);
	}

	void Application::ApplicationEventListener::OnWindowClose() {
		parentApplication_.isRunning_ = false;
		PLS_CORE_INFO("Window closed");
	}

	Application::Application() :
		moduleManager_(Pulse::Modules::ModuleManager::GetInstance()),
		applicationEventListener_(Events::IEventListener<ApplicationEventListener>::Create(*this)) {
		
		// Registering core modules
		moduleManager_.RegisterModule<Pulse::Modules::Renderer>();
		moduleManager_.RegisterModule<Pulse::Modules::Windows::WindowsWindow>();
		moduleManager_.RegisterModule<Pulse::Modules::Windows::WindowsInput>();
		moduleManager_.RegisterModule<Pulse::Modules::ImGuiModule>();
		moduleManager_.RegisterModule<Pulse::Modules::Camera>();
	}

	Application::~Application() {
		isRunning_ = false;
		moduleManager_.ShutdownModules();
	}

	void Application::Run() {
		while (isRunning_) {
			moduleManager_.GetModule < Modules::Renderer>()->BeginScene();
			moduleManager_.UpdateModules();
			moduleManager_.GetModule<Modules::ImGuiModule>()->BeginFrame();
			moduleManager_.RenderAllToImGui();
			moduleManager_.GetModule<Modules::ImGuiModule>()->EndFrame();
			moduleManager_.GetModule<Modules::Renderer>()->EndScene();
		}
	}

} // namespace Pulse