#include "pch.h"

#include "Engine.h"
#include "Pulse/Core/Logging/Log.h"

// Modules:
#include "Pulse/Modules/Window/Platform/Windows/WindowsWindowModuleImpl.h"
#include "Pulse/Modules/Input/Platform/Windows/WindowsInputModuleImpl.h"
#include "Pulse/Modules/ImGui/ImGuiModule.h"
#include "Pulse/Modules/Rendering/RendererModule.h"
#include "Pulse/Modules/Camera/CameraModule.h"

// Layers:
#include "Pulse/Layers/Application/Application.h"

namespace Pulse {

	extern Layers::Application* Layers::CreateApplication(); // Defined in the CLIENT

	// Initialize the static members
	Modules::ModuleManager* Engine::moduleManager_ = nullptr;
	Layers::LayerManager* Engine::layerManager_ = nullptr;
	TimeData Engine::timeData_ = TimeData();
	bool Engine::isRunning_ = false;

	void Engine::Initialize() {
		// Logging:
		Pulse::Log::Init();

		// Modules:
		moduleManager_ = &Modules::ModuleManager::GetInstance();
		moduleManager_->RegisterModule<Modules::RendererModule>();
		moduleManager_->RegisterModule<Modules::WindowModule, Modules::Windows::WindowsWindowModuleImpl>();
		moduleManager_->RegisterModule<Modules::InputModule, Modules::Windows::WindowsInputModuleImpl>();
		moduleManager_->RegisterModule<Modules::ImGuiModule>();
		moduleManager_->RegisterModule<Modules::CameraModule>();

		// Layers:
		layerManager_ = &Layers::LayerManager::GetInstance();
		layerManager_->AttachLayerByPointer<Pulse::Layers::Application>(Pulse::Layers::CreateApplication());

		// Initialize self:
		isRunning_ = true;
		timeData_.Initialize();
		PLS_CORE_INFO("Engine initialized.");
	}

	void Engine::Run() {
		while (isRunning_) {
			moduleManager_->GetModule<Modules::RendererModule>()->BeginScene();
			layerManager_->UpdateLayers(timeData_);
			moduleManager_->UpdateModules();
			moduleManager_->GetModule<Modules::ImGuiModule>()->BeginFrame();
			layerManager_->RenderImGuiLayers(timeData_);
			moduleManager_->RenderImGuiModules();
			moduleManager_->GetModule<Modules::ImGuiModule>()->EndFrame();
			layerManager_->RenderLayers(timeData_);
			moduleManager_->GetModule<Modules::RendererModule>()->EndScene();
			timeData_.Update();
		}
	}

	void Engine::Shutdown() {
		layerManager_->DetachAllLayers();
		moduleManager_->ShutdownModules();
	}

	void Engine::Stop(){
		isRunning_ = false;
		PLS_CORE_INFO("Engine stopped");
	}

} // namespace Pulse