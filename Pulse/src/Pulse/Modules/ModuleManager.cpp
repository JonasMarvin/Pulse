#include "pch.h"

#include "ModuleManager.h"

namespace Pulse::Modules {

	ModuleManager::ModuleManager() {
		PLS_CORE_INFO("Module manager loaded.");
	}

	ModuleManager& ModuleManager::GetInstance() {
		static ModuleManager instance;
		return instance;
	}

	void ModuleManager::UpdateModules() {
		for (auto it = modules_.rbegin(); it != modules_.rend(); ++it) {
			(*it)->Update();
		}
	}

	void ModuleManager::ShutdownModules() {
		for (auto& module : modules_) {
			module->Shutdown();
			delete module;
			module = nullptr;
		}
		modules_.clear();
		modulesMap_.clear();
		PLS_CORE_INFO("Modules have been shut down.");
	}

} // namespace Pulse::Modules