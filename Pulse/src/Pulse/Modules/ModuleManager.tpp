namespace Pulse::Modules {

	template <typename T>
	void ModuleManager::RegisterModule() {
		std::type_index typeIndex(typeid(T));
		if (modulesMap_.find(typeIndex) != modulesMap_.end()) {
			PLS_CORE_ERROR("Module {0} already registered!", typeIndex);
		}
		else {
			T* module = new T();
			modules_.push_back(module);
			modulesMap_[typeIndex] = module;
			module->Initialize();
		}
	}

	template <typename T>
	T* ModuleManager::GetModule() {
		std::type_index typeIndex(typeid(T));
		if (modulesMap_.find(typeIndex) == modulesMap_.end()) {
			PLS_CORE_ERROR("Module {0} is not registered!", typeIndex);
			return nullptr;
		}
		else {
			return static_cast<T*>(modulesMap_.at(typeIndex));
		}
	}

	template <typename T>
	void ModuleManager::UnregisterModule() {
		std::type_index typeIndex(typeid(T));
		if (modulesMap_.find(typeIndex) == modulesMap_.end()) {
			PLS_CORE_ERROR("Module {0} is not registered!", typeIndex);
		}
		else {
			T* module = modulesMap_[typeIndex];
			modules_.erase(std::remove(modules_.begin(), modules_.end(), module), modules_.end());
			modulesMap_.erase(typeIndex);
			module->Shutdown();
			delete module;
			module = nullptr;
		}
	}

} // namespace Pulse::Modules