#include "pch.h"

#include "ModuleManager.h"

namespace Pulse::Modules {

	 ModuleManager& ModuleManager::GetInstance() {
		static ModuleManager instance;
		return instance;
	}

	void ModuleManager::UpdateModules() {
		for (auto& module : modules_) {
			module->Update();
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
	}

} // namespace Pulse::Modules