#include "pch.h"

#include <glad/glad.h>

#include "Application.h"

#include "Pulse/Modules/Window/Platform/Windows/WindowsWindow.h"
#include "Pulse/Modules/Input/Platform/Windows/WindowsInput.h"
#include "Pulse/Modules/ImGui/ImGuiModule.h"

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
		moduleManager_.RegisterModule<Pulse::Modules::Windows::WindowsWindow>();
		moduleManager_.RegisterModule<Pulse::Modules::Windows::WindowsInput>();
		moduleManager_.RegisterModule<Pulse::Modules::ImGuiModule>();
	}

	Application::~Application() {
		moduleManager_.ShutdownModules();
	}

	void Application::Run() {
		while (isRunning_) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			moduleManager_.GetModule<Modules::ImGuiModule>()->BeginFrame();
			moduleManager_.RenderAllToImGui();
			moduleManager_.GetModule<Modules::ImGuiModule>()->EndFrame();
			moduleManager_.UpdateModules();
		}
	}

} // namespace Pulse