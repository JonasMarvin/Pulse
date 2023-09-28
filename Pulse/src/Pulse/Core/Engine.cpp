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
#include "Pulse/Layers/Camera/CameraLayer.h"
#include "Pulse/Layers/Application/ApplicationLayer.h"

namespace Pulse {

	extern Layers::ApplicationLayer* Layers::CreateApplication(); // Defined in the CLIENT

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
		layerManager_->AttachLayer<Layers::CameraLayer>();
		layerManager_->AttachLayerByPointer(Layers::CreateApplication());

		// Initialize self:
		isRunning_ = true;
		timeData_.Initialize();
		PLS_CORE_INFO("Engine initialized.");
	}

	void Engine::Run() {
		while (isRunning_) {
			layerManager_->UpdateLayers(timeData_);
			moduleManager_->UpdateModules();
			moduleManager_->GetModule<Modules::RendererModule>()->BeginScene();
			layerManager_->RenderLayers(timeData_);
			moduleManager_->GetModule<Modules::ImGuiModule>()->BeginFrame();
			layerManager_->RenderImGuiLayers(timeData_);
			moduleManager_->RenderImGuiModules();
			moduleManager_->GetModule<Modules::ImGuiModule>()->EndFrame();
			moduleManager_->GetModule<Modules::RendererModule>()->EndScene();
			timeData_.Update();
		}
	}

	void Engine::Shutdown() {
		layerManager_->DetachAllLayers();
		moduleManager_->ShutdownModules();
		PLS_CORE_INFO("Engine shutdown.");
	}

	void Engine::Stop(){
		isRunning_ = false;
		PLS_CORE_INFO("Engine shutting down...");
	}

} // namespace Pulse