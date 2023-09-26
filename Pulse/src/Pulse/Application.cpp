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
		moduleManager_(Modules::ModuleManager::GetInstance()),
		applicationEventListener_(Events::IEventListener<ApplicationEventListener>::Create(*this)) {
		
		// Registering core modules
		moduleManager_.RegisterModule<Modules::RendererModule>();
		moduleManager_.RegisterModule<Modules::WindowModule, Modules::Windows::WindowsWindowModuleImpl>();
		moduleManager_.RegisterModule<Modules::InputModule, Modules::Windows::WindowsInputModuleImpl>();
		moduleManager_.RegisterModule<Modules::ImGuiModule>();
		moduleManager_.RegisterModule<Modules::CameraModule>();
	}

	Application::~Application() {
		isRunning_ = false;
		moduleManager_.ShutdownModules();
	}

	void Application::Run() {
		timeData_.Initialize();
		while (isRunning_) {
			moduleManager_.GetModule <Modules::RendererModule>()->BeginScene();
			OnUpdate(timeData_);
			OnRender();
			moduleManager_.UpdateModules();
			moduleManager_.GetModule<Modules::ImGuiModule>()->BeginFrame();
			OnImGuiRender();
			moduleManager_.RenderAllToImGui();
			moduleManager_.GetModule<Modules::ImGuiModule>()->EndFrame();
			moduleManager_.GetModule<Modules::RendererModule>()->EndScene();
			timeData_.Update();
		}
	}

} // namespace Pulse