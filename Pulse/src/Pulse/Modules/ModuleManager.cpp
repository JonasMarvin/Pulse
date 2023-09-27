#include "pch.h"

#include "Pulse/Modules/ModuleManager.h"

namespace Pulse::Modules {

	ModuleManager::ModuleManager() {
		PLS_CORE_INFO("Module manager loaded.");
	}

	ModuleManager& ModuleManager::GetInstance() {
		static ModuleManager instance;
		return instance;
	}

	void ModuleManager::UpdateModules() {
		for (auto it = updatableModules_.rbegin(); it != updatableModules_.rend(); ++it) {
			(*it)->Update();
		}
	}

	void ModuleManager::RenderImGuiModules() {
		for (auto it = imGuiRenderableModules_.rbegin(); it != imGuiRenderableModules_.rend(); ++it) {
			(*it)->RenderImGui();
		}
	}

	void ModuleManager::ShutdownModules() {
		for (auto module = modules_.rbegin(); module != modules_.rend(); ++module) {
			(*module)->Shutdown();
			delete (*module);
			(*module) = nullptr;
		}
		modules_.clear();
		imGuiRenderableModulesMap_.clear();
		imGuiRenderableModules_.clear();
		updatableModulesMap_.clear();
		updatableModules_.clear();
		PLS_CORE_INFO("Modules have been shut down.");
	}

} // namespace Pulse::Modules