#include "pch.h"

#include <glad/glad.h>

#include "Application.h"

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
		// moduleManager_.RegisterModule<Pulse::Modules::Windows::WindowsWindow>();
	}

	Application::~Application() {
		moduleManager_.ShutdownModules();
	}

	void Application::Run() {

		while (isRunning_) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			moduleManager_.UpdateModules();
		}
	}

} // namespace Pulse