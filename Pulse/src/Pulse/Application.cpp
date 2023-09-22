#include "pch.h"

#include "Application.h"

#include "Pulse/Modules/Window/Platform/Windows/WindowsWindowModuleImpl.h"
#include "Pulse/Modules/Input/Platform/Windows/WindowsInputModuleImpl.h"
#include "Pulse/Modules/ImGui/ImGuiModule.h"
#include "Pulse/Modules/Rendering/RendererModule.h"
#include "Pulse/Modules/Camera/CameraModule.h"

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
		moduleManager_.RegisterModule<Pulse::Modules::RendererModule>();
		moduleManager_.RegisterModule<Pulse::Modules::WindowModule, Pulse::Modules::Windows::WindowsWindowModuleImpl>();
		moduleManager_.RegisterModule<Pulse::Modules::InputModule, Pulse::Modules::Windows::WindowsInputModuleImpl>();
		moduleManager_.RegisterModule<Pulse::Modules::ImGuiModule>();
		moduleManager_.RegisterModule<Pulse::Modules::CameraModule>();
	}

	Application::~Application() {
		isRunning_ = false;
		moduleManager_.ShutdownModules();
	}

	void Application::Run() {
		while (isRunning_) {
			moduleManager_.GetModule < Modules::RendererModule>()->BeginScene();
			OnRender();
			moduleManager_.UpdateModules();
			moduleManager_.GetModule<Modules::ImGuiModule>()->BeginFrame();
			moduleManager_.RenderAllToImGui();
			moduleManager_.GetModule<Modules::ImGuiModule>()->EndFrame();
			moduleManager_.GetModule<Modules::RendererModule>()->EndScene();
		}
	}

} // namespace Pulse