#pragma once

#include <memory>
#include <vector>

#include "Pulse/Modules/IModule.h"

namespace Pulse::Modules {

	class ModuleManager {
	public:
		// Declaratioms
		ModuleManager(const ModuleManager&) = delete;
		ModuleManager(ModuleManager&&) = delete;
		ModuleManager& operator=(const ModuleManager&) = delete;
		ModuleManager& operator=(ModuleManager&&) = delete;

		static inline ModuleManager& GetInstance();

		template <typename T>
		void RegisterModule();

		void InitializeModules() const;

		template <typename T>
		void RegisterAndInitializeModule();

		template <typename T>
		const std::shared_ptr<T> GetModule() const;

		void UpdateModules(float deltaTime) const;

		template <typename T>
		void ShutdownModule();

		void ShutdownModules();

		// Implementations
		static inline ModuleManager& GetInstance() {
			static ModuleManager instance;
			return instance;
		}

	private:
		ModuleManager() = default;
		~ModuleManager();

		std::vector<std::shared_ptr<IModule>> modules_;
	}; // class ModuleManager

} // namespace Pulse::Modules