#include "pch.h"

#include "ModuleManager.h"

namespace Pulse::Modules {

	ModuleManager::~ModuleManager(){
		ShutdownModules();
	}

	void ModuleManager::InitializeModules() const {
		for (const auto& module : modules_) {
			module->Initialize();
		}
	}

	void ModuleManager::UpdateModules(float deltaTime) const {
		for (const auto& module : modules_) {
			module->Update(deltaTime);
		}
	}

	void ModuleManager::ShutdownModules() {
		for (const auto& module : modules_) {
			module->Shutdown();
		}
		modules_.clear();
	}

} // namespace Pulse::Modules